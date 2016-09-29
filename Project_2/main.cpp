#ifndef CATCH_CONFIG_MAIN
#include <iostream>
#include <cstdlib> // use of atoi
#include <armadillo>
#include "potential.h"
#include "System.h"
#include <string>
#include "time.h"
#include <fstream>
#include <iomanip>

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
    int n = 100;
    string potential = string("HO"); // HO or CO
    cout << potential << endl;
    double rho_max = 5;

    vec omega_r = { 0.01, 0.5, 1.0, 5.0 };

    System *system = new System(n);
    mat A = system->init(rho_max, potential, omega_r(1));

    // Setting up the eigenvector matrix
    mat Z = eye<mat>(n, n);
    system->Jacobi_method(A, Z);
    int LowestIndex = system->FindLowestIndex(A);
    //cout << "LI:" << A(LowestIndex, LowestIndex) << endl;

    vec eigvals = zeros<vec>(n);
    for (int i = 0; i < n; i++) {
        eigvals(i) = A(i, i);
    }
    eigvals = sort(eigvals);
    for (int i = 0; i < 3; i++) {
        cout << setprecision(8) << "Lambda_" << i << " = " << eigvals(i) << endl;
    }
    //cout << "Lambda_0 = " << eigvals(0) << endl;

    ofstream ofile;
    ofile.open("Eigenvalues.txt");
    //ofile << "Eigenvalues: " << endl;
    for (int i = 0; i < n; i++) {
        ofile << setprecision(8) << eigvals(i) << endl;
    }
    ofile.close();



    ofile.open("Eigenvectors.txt");
    for (int i = 0; i < n; i++) {
        ofile << setprecision(8) << Z(i, LowestIndex) << endl;
    }
    ofile.close();


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
