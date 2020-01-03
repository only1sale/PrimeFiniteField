//
// Created by alex on 1/3/20.
//
#include "../include/FFp.h"
#include "../catch2/catch.hpp"

using namespace ffpp;

TEST_CASE("Testing Finite Field over a prime p class (FFp)")
{
    FFp<2> f2a = 0;
    FFp<2> f2b = 1;

    FFp<3> f3a;
    FFp<3> f3b;
    FFp<3> f3c;

    FFp<5> f5a;
    FFp<5> f5b;
    FFp<5> f5c;

    FFp<7> f7a;
    FFp<7> f7b;
    FFp<7> f7c;

    SECTION("GF2 Basic operations")
    {
        INFO("This class is primarily used for fields of char = 2! Testing Basic arithmetic!");

        //Addition
        REQUIRE(f2a + f2a == 0);
        REQUIRE(f2b + f2b == 0);
        REQUIRE(f2a + f2b == 1);
        REQUIRE(f2b + f2a == 1);

        //Subtraction
        REQUIRE(f2a - f2a == 0);
        REQUIRE(f2b - f2b == 0);
        REQUIRE(f2a - f2b == 1);
        REQUIRE(f2b - f2a == 1);

        //Multiplication
        REQUIRE(f2a * f2a == 0);
        REQUIRE(f2b * f2b == 1);
        REQUIRE(f2a * f2b == 0);
        REQUIRE(f2b * f2a == 0);

        //Division
        REQUIRE(f2b / f2b == 1);
        REQUIRE(f2a / f2b == 0);
        //Divide by zero is not defined

        //Increment
        CHECK(0 == f2a++);
        CHECK(f2a++ == 1);
        CHECK(++f2a == 1);
        CHECK(0 == ++f2a);

    }

    SECTION("GF3")
    {
        auto i = GENERATE(range(0,3));

        SECTION("Basic arithmetic")
        {
            auto j = GENERATE(range(0,3));
            f3a = i;
            f3b = j;
            f3c = f3b.minv();
            //WARN("TESTING " << f3b << " and " << f3c);
            REQUIRE((f3a + f3b) == ((i + j) %3));
            REQUIRE((f3a * f3b) == ((i * j) %3));
            REQUIRE((f3a - f3b) == ((3 + (i - j) % 3) %3));
            if(f3b != 0) { //Divide by zero not defined
                REQUIRE(1 / f3b == f3c);
                REQUIRE(1 / f3c == f3b);
                REQUIRE(f3b * f3c == 1);
            }

        }
    }

    SECTION("GF5")
    {
        auto i = GENERATE(range(0,5));

        SECTION("Basic arithmetic")
        {
            auto j = GENERATE(range(0,5));
            f5a = i;
            f5b = j;
            f5c = f5b.minv();
            REQUIRE((f5a + f5b) == ((i + j) %5));
            REQUIRE((f5a * f5b) == ((i * j) %5));
            REQUIRE((f5a - f5b) == ((5 + (i - j) % 5) %5));
            if(f5b != 0) { //Divide by zero not defined
                REQUIRE(1 / f5b == f5c);
                REQUIRE(1 / f5c == f5b);
                REQUIRE(f5b * f5c == 1);
            }

        }
    }

    SECTION("GF7")
    {
        auto i = GENERATE(range(0,7));

        SECTION("Basic arithmetic")
        {
            auto j = GENERATE(range(0,7));
            f7a = i;
            f7b = j;
            f7c = f7b.minv();
            REQUIRE((f7a + f7b) == ((i + j) %7));
            REQUIRE((f7a * f7b) == ((i * j) %7));
            REQUIRE((f7a - f7b) == ((7 + (i - j) % 7) %7));
            if(f7b != 0) { //Divide by zero not defined
                REQUIRE(1 / f7b == f7c);
                REQUIRE(1 / f7c == f7b);
                REQUIRE(f7b * f7c == 1);
            }

        }
    }
}

TEST_CASE("Testing multiplicative and additive inverse of FFp class") {

    SECTION("GF83") {
        const unsigned p = 83;


        SECTION("Additive inverse")
        {
            auto i = GENERATE(range(0,83));
            FFp<p> a = i;
            FFp<p> b = -a;
            REQUIRE(a + b == 0);
        }

        SECTION("Multiplicative inverse")
        {
            auto i = GENERATE(range(1,83));
            FFp<p> a = i;
            FFp<p> b = a.minv();
            REQUIRE(a * b == 1);
        }
    }
}