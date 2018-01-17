#ifndef CATCH_CONFIG_MAIN
#include <armadillo>
#include <cmath>
#include <cstdlib> // use of atoi
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include "potential.h"
#include "System.h"
#include "time.h"

using namespace std;
using namespace arma;

/* PLEASE READ THIS BEFORE USING THE PROGRAM!

   To use unit_test.cpp you need to uncomment DEFINES += CATCH_CONFIG_MAIN
   in Project_2.pro. This will comment out everything in main.cpp.
   After this you have to rebuild.
   Also, when going back to the main program you need to comment out
   DEFINES += CATCH_CONFIG_MAIN and then rebuild again.

   ----------

   How the program works:
   This could have been automated by using command line arguments,
   but we didn't do it - sorry!
   Before running this program you have to set up a few parameters:

   - First, choose what potential you want to use: HO, CO or HO_2e,
     where HO is the harmonic oscillator potential using one electron,
     CO is the Coulomb potential using two electrons and HO_2e is the
     harmonic oscillator potential using two electrons.
   - Choose your value of rho_max.
   - Choose your value of n.
   - Then, if you are using CO or HO_2e, choose the index w for the
     omega_r value you want:
     ( w = 0 -> omega_r = 0.01, w = 1 -> omega_r = 0.5,
     w = 2 -> omega_r = 1.0, w = 3 -> omega_r = 5.0 ).
     If you are using potential HO, then it does not matter what
     index w stands on in the range [0, 3] because it's not in use.
*/

int main() {
    string potential = string("HO"); // Choose HO, CO or HO_2e
    double rho_max = 5;              // Choose rho_max
    int n = 350;                     // Choose the value n
    int w = 0;                       // Choose index of omega_r

    // Omega_r values chosen by index w
    vec omega_r = { 0.01, 0.5, 1.0, 5.0 };

    // Naming the matrix made in the class System
    System *system = new System(n);
    mat A = system->init(rho_max, potential, omega_r(w));

    // Setting up the rotation matrix
    mat Z = eye<mat>(n, n);
    system->Jacobi_method(A, Z);

    // Armadillo function eig_sym
    system->eig_symmetric(A);

    vec eigvals = zeros<vec>(n);
    // Filling the vector eigvals with the eigenvalue corresponding to the right eigenvectors
    for (int i = 0; i < n; i++) {
        eigvals(i) = A(i, i);
    }

    // Finding the right indices for the
    uvec indices = sort_index(eigvals);

    // Sorting the eigenvalues
    eigvals = sort(eigvals);
    for (int i = 0; i < 3; i++) {
        cout << setprecision(8) << "Lambda_" << i << " = " << eigvals(i) << endl;
    }

    // Writing the eigenvalues to file
    ofstream ofile;
    string w_val = to_string(omega_r(w));
    if (potential == "HO") {
        ofile.open("../Project_2/outputs/Eigenvalues-" + potential + ".txt");
    } else if (potential == "CO" || potential == "HO_2e") {
        ofile.open("../Project_2/outputs/Eigenvalues-" + potential + "-" + "w_" + w_val + ".txt");
    }
    for (int i = 0; i < n; i++) {
        ofile << setprecision(8) << eigvals(i) << endl;
    }
    ofile.close();

    // Writing the three first eigenvectors to file
    if (potential == "HO") {
        ofile.open("../Project_2/outputs/Eigenvectors-" + potential + ".txt");
    } else if (potential == "CO" || potential == "HO_2e") {
        ofile.open("../Project_2/outputs/Eigenvectors-" + potential + "-" + "w_" + w_val + ".txt");
    }
    for (int i = 0; i < n; i++) {
        ofile << setw(25) << setprecision(8) << Z(i, indices(0));
        ofile << setw(25) << setprecision(8) << Z(i, indices(1));
        ofile << setw(25) << setprecision(8) << Z(i, indices(2)) << endl;
    }
    ofile.close();

    return 0;
}

#endif
