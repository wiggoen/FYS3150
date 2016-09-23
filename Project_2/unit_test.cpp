//#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#ifdef CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <armadillo>
#include "System.h"
#include <iostream>

using namespace std;
using namespace arma;

TEST_CASE( "Find max value", "Approximation" ) {
    int N = 3;

    // test matrix
    mat test_mat = { {1, 3, 2},
                     {3, 4, 6},
                     {2, 6, 7} };

    // getting max value from maxOffDiag
    System *offdiag = new System(N);
    int k, l;
    double max_value = offdiag->maxOffDiag(test_mat, k, l, N);

    // testing the matrix for different values, checking that it rotates
    cout << test_mat(1,2) << endl;
    REQUIRE(max_value == Approx(6));
    cout << "k = " << k << ", " << "l = " << l << endl;

    test_mat(k,l) = 0; test_mat(l,k) = 0;
    max_value = offdiag->maxOffDiag(test_mat, k, l, N);
    REQUIRE(max_value == Approx(3));

    test_mat(k,l) = 0; test_mat(l,k) = 0;
    max_value = offdiag->maxOffDiag(test_mat, k, l, N);
    REQUIRE(max_value == Approx(2));

    test_mat(k,l) = 0; test_mat(l,k) = 0;
    max_value = offdiag->maxOffDiag(test_mat, k, l, N);
    REQUIRE(max_value == Approx(0));
}



#endif
