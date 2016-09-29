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

    // testing the matrix for different values
    //cout << test_mat(1,2) << endl;
    REQUIRE(max_value == Approx(6));
    //cout << "k = " << k << ", " << "l = " << l << endl;
    //cout << test_mat << endl;

    // hard coding elements to zero and testing for the next values
    test_mat(k,l) = 0; test_mat(l,k) = 0;
    max_value = offdiag->maxOffDiag(test_mat, k, l, N);
    REQUIRE(max_value == Approx(3));
    //cout << test_mat << endl;

    test_mat(k,l) = 0; test_mat(l,k) = 0;
    max_value = offdiag->maxOffDiag(test_mat, k, l, N);
    REQUIRE(max_value == Approx(2));
    //cout << test_mat << endl;

    test_mat(k,l) = 0; test_mat(l,k) = 0;
    max_value = offdiag->maxOffDiag(test_mat, k, l, N);
    REQUIRE(max_value == Approx(0));
    //cout << test_mat << endl;
}

TEST_CASE( "Testing eigenvalues", "Approximation" ) {
    int N = 5;
    mat test_mat = { {1, 2, 3, 4, 5},
                     {2, 1, 2, 3, 4},
                     {3, 2, 1, 2, 3},
                     {4, 3, 2, 1, 2},
                     {5, 4, 3, 2, 1} };
    double lambda_0 = -5.236067977499790;
    double lambda_1 = -1.635237730041817;
    double lambda_2 = -0.763932022500212;
    double lambda_3 = -0.556294915312374;
    double lambda_4 = 13.191532645354183;

    System *test_matrix = new System(N);
    mat B = test_matrix->Jacobi_method(test_mat, N);
    vec eigvals = zeros<vec>(N);
    for (int i = 0; i < N; i++) {
        eigvals(i) = B(i, i);
    }
    eigvals = sort(eigvals);
    /*for (int i = 0; i < N; i++) {
        cout << "Lambda_" << i << " = " << eigvals(i) << endl;
    }*/
    REQUIRE(eigvals(0) == Approx(lambda_0));
    REQUIRE(eigvals(1) == Approx(lambda_1));
    REQUIRE(eigvals(2) == Approx(lambda_2));
    REQUIRE(eigvals(3) == Approx(lambda_3));
    REQUIRE(eigvals(4) == Approx(lambda_4));
}
TEST_CASE( "Testing conservation of inner product", "Approximation" ) {
    mat test_X = { {1, 0, 1, 0, 1},
                   {0, 1, 0, 1, 0} };
    mat test_Y = { {0, 1, 0, 1, 0},
                   {1, 0, 1, 0, 1} };
    double dot_product = dot(test_X, trans(test_X));
    cout << dot_product << endl;
}

#endif