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

    int w = 0; // Choose index of omega_r
    string potential = string("CO"); // Choose HO or CO
    cout << potential << endl;

    int n = 500;
    double rho_max = 50;

    vec omega_r = { 0.01, 0.5, 1.0, 5.0 };

    System *system = new System(n);
    mat A = system->init(rho_max, potential, omega_r(w));

    // Setting up the eigenvector matrix
    mat Z = eye<mat>(n, n);
    system->Jacobi_method(A, Z);

    vec eigvals = zeros<vec>(n);
    for (int i = 0; i < n; i++) {
        eigvals(i) = A(i, i);
    }

    uvec indices = sort_index(eigvals);

    eigvals = sort(eigvals);
    for (int i = 0; i < 3; i++) {
        cout << setprecision(8) << "Lambda_" << i << " = " << eigvals(i) << endl;
    }

    ofstream ofile;
    string w_val = to_string(omega_r(w));
    if (potential == "HO") {
        ofile.open("../Project_2/outputs/Eigenvalues-" + potential + ".txt");
    } else if (potential == "CO") {
        ofile.open("../Project_2/outputs/Eigenvalues-" + potential + "-" + "w_" + w_val + ".txt");
    }
    for (int i = 0; i < n; i++) {
        ofile << setprecision(8) << eigvals(i) << endl;
    }
    ofile.close();

    if (potential == "HO") {
        ofile.open("../Project_2/outputs/Eigenvectors-" + potential + ".txt");
    } else if (potential == "CO") {
        ofile.open("../Project_2/outputs/Eigenvectors-" + potential + "-" + "w_" + w_val + ".txt");
    }
    for (int i = 0; i < n; i++) {
        ofile << setw(15) << setprecision(8) << Z(i, indices(0));
        ofile << setw(15) << setprecision(8) << Z(i, indices(1));
        ofile << setw(15) << setprecision(8) << Z(i, indices(2)) << endl;
    }
    ofile.close();

    return 0;
}

#endif
