// Running all tests in tests/FFprimeTest.cpp

//#define CATCH_CONFIG_MAIN

#define CATCH_CONFIG_RUNNER

#include "catch2/catch.hpp"

#include <iostream>
#include "include/FFp.h"
#include "include/Polynomial.h"

using namespace std;
using namespace ffpp;

int main() {
    PrimePolynomial<5> a = {1,2,3,4,5};
    PrimePolynomial<5> b = {1,2,3,4,5, 6, 7};


    cout << a - b  << "<=> " << b - a<< endl;

    Polynomial<double> x = {2, -1, 1};
    Polynomial<double> y = {-10,0,1,3,-4,5};
    Polynomial<double> c = y / x;
    Polynomial<double> d = y % x;

    cout << c << endl << d << endl;


}
