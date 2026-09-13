#define BOOST_TEST_MODULE calc test
#include <boost/test/included/unit_test.hpp> //this is the most basic
#include <boost/test/data/test_case.hpp>   // and this to get the parametric test define
#include <boost/test/data/monomorphic.hpp> // we use this to define datasets

#include <vector>     // this for the ds
#include <variant>    // this to return quite retarded stuff inside functions
#include <exception>  // this to make a custom exception, very good!

using fpvar = float;
using intvar = int;
namespace bdata = boost::unit_test::data;
#define DEBUG

//ah yeah, to insta-fail something, we may use a static_assert("implement me :)", false);

/* 

// example dataset found at -> https://www.boost.org/doc/libs/latest/libs/test/doc/html/boost_test/tests_organization/test_cases/test_case_generation/datasets.html

class fibonacci_dataset {
public:
    // the type of the samples is deduced
    static const int arity = 1;

    struct iterator {

        iterator() : a(1), b(1) {}

        int operator*() const   { return b; }
        void operator++()
        {
            a = a + b;
            std::swap(a, b);
        }
    private:
        int a;
        int b; // b is the output
    };

    fibonacci_dataset()             {}

    // size is infinite
    bdata::size_t   size() const    { return bdata::BOOST_TEST_DS_INFINITE_SIZE; }

    // iterator
    iterator        begin() const   { return iterator(); }
};
*/

////////DATASETS


//this one GAVE ME HELLA FUCKING TROUBLE earlier. Not fun! But very general! also it seems to need an overloaded << operator for the ostream thingy...
template <typename t>
std::ostream &operator<<(std::ostream &stream, const std::vector<t> &vec){ 
    stream << "\n{";
    //big rant: 
    //ah yeah, this means if ye perhaps by fate or misadventure find yourself trying to print a 
    /*
        std::vector<
            std::queue<
                std::vector<
                    std::map<
                        std::vector<
                            std::deque<t>
                        >,
                        std::vector<
                            std::map<t, t>
                        >
                    >
                >
            >
        >
    */
   //inshallah, you'll also need overloads for queue, deque and map.

   // of course, what I actually intended was for some convenient way to verify passed container type 
   // is a blasted container and stuff, but that would probably require advanced black magic.
   // then, we'd have a template <typename t, class container> and some convenient way to check at the very least
   // container got a .begin() and a .end()!

   //tl;dr -> not general enough overload. This works for std::vector, Amen.
    for(auto a: vec){
        stream << a << ' ';
    }
    stream << "}\n";
    return stream;
};

// and finally, the cursed dataset!

class i_ops_dataset{
    private:
        intvar start;
    public:
        i_ops_dataset(): start{0} {};
        i_ops_dataset(intvar var): start{var} {};

        static const int arity = 1; //since we'll need a triad of op1, op2, op3 to do stuff.

        struct iterator {
            iterator()                         : op1{1}   , op2{1}    { res = op1 + op2;};
            iterator(intvar var1, intvar var2) : op1{var1}, op2{var2} { 
                if(!var1 && var2){
                    op2++;
                    op1++;
                }
                
                res = op1 + op2;

            };

            std::vector<intvar> operator*() const { return {op1, op2, res}; };
            void operator++(){
                op1 *= 2;
                op2 *= 3;
                res = op1 + op2;
            };

            private:
                intvar op1;
                intvar op2;
                intvar res;
        };
        //   also, why do we need another blasted size_t?
        //      V
        bdata::size_t   size()  const { return bdata::BOOST_TEST_DS_INFINITE_SIZE; }; //had to get this outta wacka blasted test/data. Criiiinge
        //it seems to only add support to inf operations and stuff.
        iterator        begin() const { 
            if(!start) return iterator();
            return iterator(start, start + 3);
        };
};


//works like a iota. Very fun!
class i_ops_dataset_iota{
    private:
        intvar start;
    public:
        i_ops_dataset_iota(intvar var = 0): start{var} {};

        static const int arity = 1; //since we'll need a triad of op1, op2, op3 to do stuff.

        struct iterator {
            iterator()        : op{0}   {};
            iterator(int var) : op{var} {};


            intvar operator*() const { return op; };
            void operator++(){
                op += 1;
            };

            private:
                intvar op;
        };
        //   also, why do we need another blasted size_t?
        //      V
        bdata::size_t   size()  const { return bdata::BOOST_TEST_DS_INFINITE_SIZE; }; //had to get this outta wacka blasted test/data. Criiiinge
        //it seems to only add support to inf operations and stuff.
        iterator        begin() const { return iterator(start);};
};

class f_ops_dataset{
    public:
        f_ops_dataset() {}
        static const int arity = 1; //since we'll need a triad of op1, op2, op3 to do stuff.

        struct iterator {
            iterator() : op1(1), op2(1), res(2) {}

            std::vector<fpvar> operator*() const { return {op1,op2,res}; }
            void operator++(){
                //ah yea, can't wait till this loses every semblance of precision...
                op1 += 1;
                op2 += 2;
                res = op1 + op2;
            }

            private:
                fpvar op1;
                fpvar op2; 
                fpvar res;
        };
        //   also, why do we need another blasted size_t?
        //      V
        bdata::size_t   size() const    { return bdata::BOOST_TEST_DS_INFINITE_SIZE; } //had to get this outta wacka blasted test/data. Criiiinge
        //it seems to only add support to inf operations and stuff.
        iterator begin(){ return iterator();};
};

// and register these datasets as legit else code fucking crashes and burns...
namespace boost { namespace unit_test { namespace data { namespace monomorphic {
  template <>
  struct is_dataset<i_ops_dataset_iota> : boost::mpl::true_ {};
}}}}

namespace boost { namespace unit_test { namespace data { namespace monomorphic {
  template <>
  struct is_dataset<f_ops_dataset> : boost::mpl::true_ {};
}}}}

////////CUSTOM EXCEPTIONS

// we're using this for exception requirement handling!
// https://www.boost.org/doc/libs/latest/libs/test/doc/html/boost_test/utf_reference/testing_tool_ref/assertion_boost_level_exception.html
// and this for how to actually inherit exception and throw a graceful exception
//https://www.geeksforgeeks.org/cpp/exception-handling-c/

class NullPopException : public std::exception {
    int value;
public:
    // Constructor
    NullPopException(int val) : value(val) {}

    // Override what() method
    const char* what() const noexcept override {
        std::string errmsg = "Calculator "; 
        errmsg+= value ? "i_stack": "f_stack";
        errmsg+= " popped, but stack is empty!";
        return errmsg.c_str();
    }

    // Optional: method to get the invalid value
    int getValue() const {
        return value;
    }
};
// as nullpopexception will have value of mode of exception, then as i_mode is 0, we may use this expression!
bool integer_mode_exception( const NullPopException &err ){
    return !err.getValue(); 
}

////////CALCULATOR CLASS

class Calc{
        intvar i_op1;
        intvar i_op2;
        intvar intres;
        fpvar  f_op1;
        fpvar  f_op2;
        fpvar  fpres;

        std::vector<intvar> i_stack;
        std::vector<fpvar>  f_stack;
        intvar              reduce_int;
        fpvar               reduce_float;
        
        int mode; // 0 -> int operation mode; 1 -> float operation mode; We only got two operation modes anyway;
        
    public:
        Calc() = default;
        ~Calc() = default;
        
        template <typename t>
        void setop1(t var){
            if(mode){
                static_assert( std::is_floating_point<t>::value == true );
                f_op1 =  var;
                return;
            }
            static_assert(std::is_integral<t>::value == true);
            i_op1 = var;
        }
        
        template <typename t>
        void setop2(t var){
            if(mode){

                #ifdef DEBUG
                std::cout << "DEBUG: function setop2; passed var: " << var << "| \n";
                #endif
                
                static_assert(std::is_floating_point<t>::value == true);
                f_op2 =  var;
                return;
            }
            static_assert( std::is_integral<t>::value == true);
            i_op2 = var;

        }
        
        std::variant<std::pair<intvar, intvar>, std::pair<fpvar,fpvar>> getops(){
            std::variant<std::pair<intvar, intvar>, std::pair<fpvar,fpvar>> ret;
            if(mode){
                ret = std::pair<fpvar, fpvar>({f_op1, f_op2});
            } else{
                ret = std::pair<intvar, intvar>({i_op1, i_op2});
            }
            return ret;
        }

        std::variant<intvar, fpvar> getres(){
            std::variant<intvar, fpvar> ret;
            if(mode){
                ret = fpres;
            } else{
                ret = intres;
            }
            return ret;
        }

        std::variant<intvar, fpvar> top(){
            std::variant<intvar, fpvar> ret;
            if(mode){
                ret = f_stack.back();
            } else
                ret = i_stack.back();
            return ret;
        }
        
        void pop(){
            if(mode){
                if(f_stack.size() < 1) throw NullPopException(mode);
                f_stack.pop_back();
            }else{
                if(i_stack.size() < 1) throw NullPopException(mode);
                i_stack.pop_back();
            }
        }
        

        int getmode(){
            return mode;
        }

        void swapmode(){
            this->mode = !this->mode;
        }

        void acc(){
            if(mode){
               fpres = f_op1 + f_op2; 
                return;
            }

            intres = i_op1 + i_op2;
        }

        

        template <typename t>
        void push(t var){
            if(mode){
                f_stack.emplace_back(var);
                return;
            }
            i_stack.emplace_back(var);
        }

        

        int getstacksize(){
            return 0;
        }
        
        void clear(){
            i_op1        = 0;
            i_op2        = 0;
            intres       = 0;
            f_op1        = 0;
            f_op2        = 0;
            fpres        = 0;
            reduce_float = 0;
            reduce_int   = 0;

            i_stack      . clear();
            f_stack      . clear();
            
            mode = 0;
        }

        
        

    };

struct calc_fixture{
    Calc *c;
    calc_fixture(){
        BOOST_TEST_MESSAGE("CREATING CALCULATOR!");
        c = new Calc();
    }
    ~calc_fixture(){
        BOOST_TEST_MESSAGE("DESTROYING CALCULATOR");
        delete c;
    }
};
BOOST_AUTO_TEST_SUITE( basics )
BOOST_FIXTURE_TEST_CASE(test_modeswap, calc_fixture){
    //we expect mode to be initialized as 0
    BOOST_TEST(c->getmode() == 0);
    c->swapmode(); //then swapmode should, of course, flip this sucker so behaviour changes :>
    BOOST_TEST(c->getmode() == 1);
}

//checks initialization and stuff...
BOOST_FIXTURE_TEST_CASE(test_gettingOperands, calc_fixture){
    c->clear();
    BOOST_TEST(c->getmode() == 0);
    int op1 = std::get<std::pair<intvar, intvar>>(c->getops()).first;
    int op2 = std::get<std::pair<intvar, intvar>>(c->getops()).second;
    BOOST_TEST(op1 == 0);
    BOOST_TEST(op2 == 0);
}

BOOST_FIXTURE_TEST_CASE(test_stack1, calc_fixture){
    c->clear();
    BOOST_TEST(!c->getmode());
    c->push(5);
    c->push(6);
    c->push(7); //then, this should be on top and should be accessible as .top();
    
    //checks to see if top works as expected!
    BOOST_TEST(std::get<int>(c->top()) == 7);
    c->pop(); 
    BOOST_TEST(std::get<int>(c->top()) == 6);
    c->pop();
    c->pop();

    //also, we should expect at the very least some exception if you pop and stack is empty!
    //and, of course, the code carried should be in i_mode, aka mode == 0;
    BOOST_CHECK_EXCEPTION( c->pop(), NullPopException, integer_mode_exception); //Alright! blasted nullpopexcept seems to be working fine :>    
}
BOOST_AUTO_TEST_SUITE_END()



//NOW WE GOT PARAMETRIZED TESTS IN CPP YE BASTARDS YE FUCKING FOOLS -> FUCKING GO!
#define PARAM_TEST_SIZE 3 //increase if you wish to take longer, three is alright for this one...

BOOST_DATA_TEST_CASE(test_i_ops_dataset_iota, (i_ops_dataset_iota() ^ bdata::xrange(PARAM_TEST_SIZE)) ^ i_ops_dataset_iota(5), op1, counter, op2){
    BOOST_TEST(op2 == op1 + 5); 
}


//for whatever reason, this test needs an overloaded ostream operator<< able to print the std::vector :>
//tests the dataset with the std::vector<intvar>(3) return type 
BOOST_DATA_TEST_CASE(test_i_ops_dataset_vector_return, i_ops_dataset() ^ bdata::xrange(PARAM_TEST_SIZE), ops, counter){
    BOOST_TEST(ops.size() == 3);
    auto op1 = ops[0];
    auto op2 = ops[1];
    auto res = ops[2];
    BOOST_TEST(op1 + op2 == res);  
}



// now, we may move on to test other stuff, like parametrized fixtured test cases...
// and also write the specification for a parametrized acc test! also, registering operations :>>>

BOOST_DATA_TEST_CASE_F(calc_fixture, test_op_registration, (i_ops_dataset_iota() ^ bdata::xrange(PARAM_TEST_SIZE)) ^ i_ops_dataset_iota(5), op1, counter, op2){
    c->clear();
    BOOST_TEST(c->getmode() == 0); //make sure you're operating in integer mode, you absolute buffoon. 
    //then, we may register the ops inside the calculator...
    c->setop1(op1);
    c->setop2(op2);
    c->acc();
    if(c->getmode()){
        auto res = std::get<fpvar>(c->getres());
    }
    auto res = std::get<intvar>(c->getres());
    BOOST_TEST(op1+op2 == res); 
}

/*
BOOST_DATA_TEST_CASE_F(calc_fixture, test_parametric_i_ops, i_ops_dataset() ^ bdata::xrange(PARAM_TEST_SIZE), sample, counter){
    //now, I'm doing something quite dire here -> the sample SHOULD be a vector of size 3;
    //The builtin typechecker got no idea what the fuck is going on inside this blasted 
    BOOST_TEST(!c->getmode()); //make sure we're running under integer operation mode
    BOOST_TEST(std::is_floating_point_v<typeid>)
    c->setop1(sample[0]);
    c->setop2(sample[1]);
    c->acc();
    BOOST_TEST(std::get<int>(c->getres()) == sample[2]); //waaaa, ints are soo goood to meeee >.<
}
*/

//ah yeah, comparing two floats is NOTORIOUSLY FREAKY HORNY BLASTED ULTRA SUPER HARD and requires !le extra mile!
// which was GRACIOUSLY provided by Bruce Dawson in his blog post -> https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
// stand in the shoulders of giants, they sayeth!


/*
//anyway, the fabs <= epsilon approach should serve us "WELL ENOUGH"

#define LSX .000001 //eh, small'nuff
BOOST_DATA_TEST_CASE_F(calc_fixture, test_parametric_f_ops, f_ops_dataset() ^ bdata::xrange(PARAM_TEST_SIZE), sample, counter){
    //now, I'm doing something quite dire here -> the sample SHOULD be a vector of size 3;
    //The builtin typechecker got no idea what the fuck is going on inside this blasted 
    c->swapmode();
    BOOST_STATIC_ASSERT(c->getmode()); //make sure we're fp operation mode...
    c->setop1(sample[0]);
    c->setop2(sample[1]);
    c->acc();
    BOOST_TEST(fabs(std::get<fpvar>(c->getres()) - sample[2]) <= LSX) //my constant, I name it whatever I need(/want) :>>
}

*/

//define cleanup before things get messy down there. Later...
#ifdef LSX
#undef LSX
#endif
#ifdef PARAM_TEST_SIZE
#undef PARAM_TEST_SIZE
#endif