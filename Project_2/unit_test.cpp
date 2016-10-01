//#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#ifdef CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "System.h"
#include <armadillo>
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
    System* system = new System(N);
    double max_value = system->maxOffDiag(test_mat);
    int &l = system->l;
    int &k = system->k;

    // testing that the matrix gets the correct largest non-diagonal elements in upper triangle
    REQUIRE(max_value == Approx(6));

    // hard coding elements to zero and testing for the next elements
    test_mat(k, l) = 0; test_mat(l, k) = 0;
    max_value = system->maxOffDiag(test_mat);
    REQUIRE(max_value == Approx(3));

    test_mat(k, l) = 0; test_mat(l, k) = 0;
    max_value = system->maxOffDiag(test_mat);
    REQUIRE(max_value == Approx(2));

    test_mat(k, l) = 0; test_mat(l, k) = 0;
    max_value = system->maxOffDiag(test_mat);
    REQUIRE(max_value == Approx(0));
}

TEST_CASE( "Testing eigenvalues", "Approximation" ) {
    int N = 5;

    // test matrix
    mat test_mat = { {1, 2, 3, 4, 5},
                     {2, 1, 2, 3, 4},
                     {3, 2, 1, 2, 3},
                     {4, 3, 2, 1, 2},
                     {5, 4, 3, 2, 1} };

    // setting up the rotation matrix
    mat test_mat_Z = eye<mat>(N, N);

    // known eigenvalues from test matrix
    double lambda_0 = -5.236067977499790;
    double lambda_1 = -1.635237730041817;
    double lambda_2 = -0.763932022500212;
    double lambda_3 = -0.556294915312374;
    double lambda_4 = 13.191532645354183;

    // using Jacobi method to find the eigenvalues
    System *test_matrix = new System(N);
    test_matrix->Jacobi_method(test_mat, test_mat_Z);

    // setting up the eigenvalue vector
    vec eigvals = zeros<vec>(N);
    for (int i = 0; i < N; i++) {
        eigvals(i) = test_mat(i, i);
    }
    // sorting the eigenvalues
    eigvals = sort(eigvals);

    // testing that the eigenvalues are correct
    REQUIRE(eigvals(0) == Approx(lambda_0));
    REQUIRE(eigvals(1) == Approx(lambda_1));
    REQUIRE(eigvals(2) == Approx(lambda_2));
    REQUIRE(eigvals(3) == Approx(lambda_3));
    REQUIRE(eigvals(4) == Approx(lambda_4));
}

#endif
