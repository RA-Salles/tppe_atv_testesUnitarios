//Esse arquivo apresenta um teste que passa
#define BOOST_TEST_MODULE testes_lentos
#include "./common/imports.hpp"


//This type of macro does generate some kind of strangement 
//by part of the author, since it creates a region in which no
//delimiters except macros are present.

BOOST_AUTO_TEST_SUITE(AppTest) // <<<< this delimiter

    BOOST_AUTO_TEST_CASE(assertTrueTest){
        BOOST_TEST_MESSAGE("Welcome to Boost.test!\n");
        BOOST_TEST(true);
    }

BOOST_AUTO_TEST_SUITE_END()    // <<<< and this delimiter

//which is not great at all, but it was probably a hotfix which became 
//part of the library and changing it now would cause great distress
//to toolchain and systems programmers :)