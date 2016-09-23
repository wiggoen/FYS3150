
#ifndef CATCH_CONFIG_MAIN
#include <iostream>
#include <cstdlib> // use of atoi
#include <armadillo>
#include "potential.h"
#include "System.h"
#include <string>

using namespace std;
using namespace arma;

int main()//(int argc, char *argv[])
{
    // check that we have 1 argument (number of elements N for the symmetric matrix)
   /* if (argc <= 1) {
        cout << "Bad usage: " << argv[0] << endl;
        cout << "Choose potential HO (harmonic oscillator) or CO (coulomb)!" << endl;
        //cout << "You need to specify the number of N elements for the matrix in command line!" << endl;
        exit(1);
        }

    // Declaring variables
    char potential =  argv[1]; // first command line argument
    //int N = atoi(argv[1]); // first command line argument
    */
    int N = 100;
    string potential = string("CO"); // HO or CO
    cout << potential << endl;
    double rho_max = 3.6;

    vec omega_r = { 0.01, 0.5, 1.0, 5.0 };

    System *A_matrix = new System(N);
    mat A = A_matrix->init(N, rho_max, potential, omega_r(1));
    //cout << "A-matrix:" << endl;
    //cout << A << endl;

    mat B = A_matrix->Jacobi_method(A, N);
    //cout << "Diagonal matrix:" << endl;
    //cout << B << endl;

    /*int k, l;
    System *offD = new System(N);
    double X = offD->maxOffDiag(A, k, l, N);
    cout << "max: " << X << endl;
    cout << "k: " << k << endl;
    cout << "l: " << l << endl;
    */
    vec eigvals = zeros<vec>(N);
    for (int i = 0; i < N; i++) {
        eigvals(i) = B(i, i);
    }
    eigvals = sort(eigvals);
    for (int i = 0; i < 3; i++) {
        cout << "Lambda_" << i << " = " << eigvals(i) << endl;
    }
    //cout << "Lambda_0 = " << eigvals(0) << endl;


    return 0;
}

/*
main() {
    void f(int &k) {
        k = 10000;
    }
    int k = 9;
    f(k);
    cout << k << endl; // 1000
}*/

#endif
