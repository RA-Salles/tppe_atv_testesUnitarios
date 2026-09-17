//Esse arquivo apresenta o estilo de escrita de um teste em boost.test
#define BOOST_TEST_MODULE testes_lentos
#include <boost/test/included/unit_test.hpp> // essa é a importação mais básica
#include <boost/test/data/test_case.hpp>     // and this to get the parametric test define
#include <boost/test/data/monomorphic.hpp>   // we use this to define datasets

#include "../../main/service/service.hpp" // and this so we have imports, classes, definitions etc. from the tested system!

namespace utf = boost::unit_test; //you need this else the compiler will complain because 

struct F {
  F()  { BOOST_TEST_MESSAGE( "setup fixture" ); }
  ~F() { BOOST_TEST_MESSAGE( "teardown fixture" ); }
};

//create a suite for your module...git 
BOOST_AUTO_TEST_SUITE(suiteExemplo, * utf::fixture<F>())

    BOOST_AUTO_TEST_CASE(test_case1){
        BOOST_TEST_MESSAGE("running test_case1");
        BOOST_TEST(true);
    }



BOOST_AUTO_TEST_SUITE_END()