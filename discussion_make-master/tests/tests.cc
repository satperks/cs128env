//////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up                             //
//////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN
#endif
#include "catch.hpp"

//////////////////////////////////////////////////////////////////////////////
//                                 Includes                                 //
//////////////////////////////////////////////////////////////////////////////
#include "factorial.h"
#include "point.h"

//////////////////////////////////////////////////////////////////////////////
//                                Test Cases                                //
//////////////////////////////////////////////////////////////////////////////

TEST_CASE( "Factorials are computed", "[factorial]" ) {
    REQUIRE( Factorial(1) == 1 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 6 );
    REQUIRE( Factorial(10) == 3628800 );
}

TEST_CASE( "Point equality", "[points]" ) {
    Point p1(255, 255, 255);
    Point p2(255, 255, 255);
    Point p3(0, 0, 0);

    REQUIRE ( p1 == p2 );
    REQUIRE ( p2 == p1 );
    REQUIRE ( p1 != p3 );
    REQUIRE ( p3 != p1 );
}

TEST_CASE( "Point distance", "[points]" ) {
    Point p1(0, 0, 0);
    Point p2(3, 4, 0);

    REQUIRE ( p1.len() == 0.0 );
    REQUIRE ( p2.len() == 5.0 );
}

//////////////////////////////////////////////////////////////////////////////