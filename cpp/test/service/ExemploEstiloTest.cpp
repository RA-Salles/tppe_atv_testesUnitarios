//Esse arquivo apresenta o estilo de escrita de um teste em boost.test
#define BOOST_TEST_MODULE testes_lentos
#include <boost/test/included/unit_test.hpp> // essa é a importação mais básica
#include <boost/test/data/test_case.hpp>     // and this to get the parametric test define
#include <boost/test/data/monomorphic.hpp>   // we use this to define datasets

#include "../../main/service/service.hpp" // and this so we have imports, classes, definitions etc. from the tested system!
#include "../../main/common/imports.hpp"
namespace utf = boost::unit_test; //you need this else the compiler will complain because 
using namespace fga0242::service;

double const comparisonDelta = 1e-6;

//that setup step inside the OG .java actually needs a fixture. So we'll do just that :)
struct productFixture1 {
    Produto *p;
    //this mimicks the Produto() initializer...
    //BEWARE:
    //FORGETTING TO PASS A VALID ID !WILL!
    //USE THE NO ARGUMENT CONSTRUCTOR
    // inshallah
    productFixture1(std::string id = "", std::string name = "", std::string type = "", double price = 0, double weight = 0 ){ 
        BOOST_TEST_MESSAGE( "setting up product fixture :)" );
        if(id.size())
            p = new Produto();
        else
            p = new Produto(id, name, type, price, weight);
    }
    ~productFixture1(){
        BOOST_TEST_MESSAGE( "killing product >:" ); 
        delete p;
    }
};

struct productFixture2 {
    Produto *p;
    //this mimicks the Produto() initializer...
    productFixture2(std::string id = "P001", std::string name = "Tomate", std::string type = "HORTIFRUTI", double price = 1, double weight = 4.5 ){ 
        BOOST_TEST_MESSAGE( "setting up product fixture :)" );
        p = new Produto(id, name, type, price, weight);
    
    }
    ~productFixture2(){
        BOOST_TEST_MESSAGE( "killing product >:" ); 
        delete p;
    }
};

struct productFixture3 {
    Produto *p;
    //this mimicks the Produto() initializer...                 //can't use the ã else I'll pay.
    productFixture3(std::string id = "P002", std::string name = "Melao", std::string type = "HORTIFRUTI", double price = 0, double weight = 0 ){ 
        BOOST_TEST_MESSAGE( "setting up product fixture :)" );
        p = new Produto(id, name, type, price, weight);
    
    }
    ~productFixture3(){
        BOOST_TEST_MESSAGE( "killing product >:" ); 
        delete p;
    }
};

struct itemOrderFixture {
    Produto *p;
    ItemPedido *ip;
    //this mimicks the Produto() initializer...                 
    itemOrderFixture(std::string id = "P003", std::string name = "Biscoito Negesseco", std::string type = "BISCOITO", double price = 4.5, double weight = 1.0 ){ 
        BOOST_TEST_MESSAGE( "setting up product fixture :)" );
        p = new Produto(id, name, type, price, weight);
        ip = new ItemPedido(*p, 3); //gotta watch out for those damn pointers.
    }
    ~itemOrderFixture(){
        BOOST_TEST_MESSAGE( "killing product >:" ); 
        delete p;
        delete ip;
    }
};



//create a suite for your module...

//watch out! Since this is basically a bunch of poorly disguised macros, 
//you'll program with your tabs or you'll lose sense of what the fuck
//is going on!

/*
    This suite should test the product methods. 
    Every
        method!

    
*/
BOOST_AUTO_TEST_SUITE(suiteProduto) //correct way would be to pass the fixture as a suite scope fixture.
    //then, create test cases!
    BOOST_FIXTURE_TEST_CASE(testProductInitialization, productFixture1){ //OK!
        BOOST_TEST_MESSAGE("TESTING FOR DEFAULT INITIALIZATION OF PRODUCT..."); //say something!

        //let's see if initialization passed alright...
        BOOST_TEST(p->getId() == ""); //then assert stuff...
        BOOST_TEST(p->getCategoria() == ""); //then assert stuff...
        BOOST_TEST(p->getPesoKg() - 0.0 <= comparisonDelta ); //then assert stuff...
        BOOST_TEST(p->getPrecoUnitario() - 0.0 <= comparisonDelta); //then assert stuff...

    }

    BOOST_FIXTURE_TEST_CASE(testProductSpecifiedInitialization, productFixture2){
        BOOST_TEST_MESSAGE("TESTING FOR p->Product(...)"); //say something!
        //str asserts
        BOOST_TEST(!std::strcmp(p->getId()       .c_str() , "P001"      )); 
        BOOST_TEST(!std::strcmp(p->getCategoria().c_str() , "HORTIFRUTI")); 
        BOOST_TEST(!std::strcmp(p->getNome()     .c_str() , "Tomate"    )); 
        //double asserts
        BOOST_TEST(p->getPesoKg()        - 4.5 <= comparisonDelta );                
        BOOST_TEST(p->getPrecoUnitario() - 1   <= comparisonDelta );            
    }

    // BY THE LORD, I CANNOT FATHOM THE JOY OF KNOWING THIS ACTUALLY WORKS!
    
    BOOST_FIXTURE_TEST_CASE(testItemOrder_Subtotal, itemOrderFixture){
        BOOST_TEST_MESSAGE("TESTING FOR itemPedido::getSubtotal()");
        //itemOrder created during fixture constructor, so we're all good!
        double subtotal = ip->getSubtotal(); //great stuff!
        BOOST_TEST(subtotal - 13.50 <= comparisonDelta);
    }

    BOOST_FIXTURE_TEST_CASE(testItemOrder_getQuantidade, itemOrderFixture){
        //as with fixtures, we're dealing with a pointer to an outerworldly
        //ghoulish hellish object...
        //We should use protection
        BOOST_TEST(ip != nullptr);
        //then we're set!
        BOOST_TEST_MESSAGE("TESTING FOR itemPedido::getQuantidade()");
        int qt = ip->getQuantidade();
        //equalshmmmm?
        BOOST_TEST(!(qt - 3));
    }

    BOOST_FIXTURE_TEST_CASE(testItemOrder_getPesoTotal, itemOrderFixture){
        BOOST_TEST(ip != nullptr);
        BOOST_TEST_MESSAGE("TESTING FOR itemPedido::getPesoTotal()");
        double wt = ip->getPesoTotal();
        BOOST_TEST(wt - 3.0 <= comparisonDelta);
    }

    // This also passed..
    BOOST_FIXTURE_TEST_CASE(testItemOrder_getProduto, itemOrderFixture){
        BOOST_TEST_MESSAGE("TESTING FOR itemPedido::getProduto()");
        //Product p and itemProduct
        Produto p = ip->getProduto();
        BOOST_TEST( &p != nullptr);
        //this is the s
        std::string id   = "P003"               ;
        std::string name = "Biscoito Negesseco" ;
        std::string type = "BISCOITO"           ;
        double price     = 4.5                  ;
        double weight    = 1.0                  ;
        BOOST_TEST( std::strcmp(p.getId()        .c_str(), id  .c_str()) == 0 );
        BOOST_TEST( std::strcmp(p.getCategoria() .c_str(), type.c_str()) == 0 ); 
        BOOST_TEST( std::strcmp(p.getNome()      .c_str(), name.c_str()) == 0 ); 
        BOOST_TEST( p.getPesoKg()        - weight <= comparisonDelta ); 
        BOOST_TEST( p.getPrecoUnitario() - price  <= comparisonDelta ); 

    }
BOOST_AUTO_TEST_SUITE_END()