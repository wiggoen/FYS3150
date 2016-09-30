#include "System.h"
#include "potential.h"
#include "time.h"
#include <armadillo>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;
using namespace arma;

System::System(int size) {
    N = size;
}

// Constructing the matrix A
mat System::init(double rho_max, string potential, double omega_r) {
    Potential* V = new Potential();
    //cout << omega_r << endl;
    mat A = zeros<mat>(N, N);

    double h = rho_max/N;
    double ei = 1.0/(h*h);

    for (int i = 0; i < N; i++) {
        if (potential == "HO") {
            A(i, i) = 2.0*ei + V->HarmonicOscillator((i+1)*h);
        } else if (potential == "CO") {
            A(i, i) = 2.0*ei + V->Coulomb(omega_r, (i+1)*h);
        } else if (potential == "HO_2e") {
            A(i, i) = 2.0*ei + V->HO_2e(omega_r, (i+1)*h);
        } if (i < N-1) {
            A(i, i+1) = -ei;
            A(i+1, i) = -ei;
        }
    }
    return A;
}

// Jacobi's method for finding eigenvalues and eigenvectors of the symmetric matrix A
void System::Jacobi_method(mat &A, mat &Z) {
    double epsilon = 1.0e-8;
    double max_number_iterations = (double) N * (double) N * (double) N;
    int iterations = 0;
    double max_OffDiag = maxOffDiag(A);

    // Runtime for the Jacobi method
    clock_t start, finish;
    // Start clock
    start = clock();

    while (fabs(max_OffDiag) > epsilon && (double) iterations < max_number_iterations) {
        max_OffDiag = maxOffDiag(A);
        rotate(A, Z);
        iterations++;
    }
    // End clock
    finish = clock();

    std::cout << "Number of iterations: " << iterations << "\n";

    // Time used
    double runtime_JM = ((finish - start)/double(CLOCKS_PER_SEC));
    cout << setiosflags(ios::showpoint | ios::uppercase);
    cout << setprecision(8) << setw(15) << "Runtime of Jacobi method = " << runtime_JM << " s" << endl;

}

// Function to find the maximum matrix element
double System::maxOffDiag(mat A) {
    double max = 0.0;

    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (fabs(A(i, j)) > max) {
                max = fabs(A(i, j));
                this->l = i;
                this->k = j;
            }
        }
    }
    return max;
}

// Function to find the values of cos and sin
void System::rotate(mat &A, mat &Z) {
    double s, c;
    if (A(k, l) != 0.0) {
        double t, tau;
        tau = (A(l, l) - A(k, k))/(2.0*A(k, l));
        if (tau > 0) {
            t = 1.0/(tau + sqrt(1.0 + tau*tau));
        } else {
            t = -1.0/(-tau + sqrt(1.0 + tau*tau));
        }
        c = 1.0/sqrt(1.0 + t*t);
        s = c*t;
    } else {
        c = 1.0;
        s = 0.0;
    }
    double a_kk, a_ll, a_ik, a_il, r_ik, r_il;
    a_kk = A(k, k);
    a_ll = A(l, l);
    // changing the matrix elements with indices k and l
    A(k, k) = c*c*a_kk - 2.0*c*s*A(k, l) + s*s*a_ll;
    A(l, l) = s*s*a_kk + 2.0*c*s*A(k, l) + c*c*a_ll;
    // hard-coding zeros
    A(k, l) = 0.0;
    A(l, k) = 0.0;
    // change the remaining elements
    for (int i = 0; i < N; i++) {
        if (i != k && i != l) {
            a_ik = A(i, k);
            a_il = A(i, l);
            A(i, k) = c*a_ik - s*a_il;
            A(k, i) = A(i, k);
            A(i, l) = c*a_il + s*a_ik;
            A(l, i) = A(i, l);
        }
        // compute the new eigenvectors
        r_ik = Z(i, k);
        r_il = Z(i, l);
        Z(i, k) = c*r_ik - s*r_il;
        Z(i, l) = c*r_il + s*r_ik;
    }
}

void System::eig_symmetric(mat &A) {
    // Calculate computation time and eigenvectors with standard Armadillo library
    clock_t start_arma, finish_arma;
    start_arma = clock();
    mat eigvec;
    vec eigval;

    //
    eig_sym(eigval, eigvec, A);
    finish_arma = clock();

    // Time used
    double runtime_arma = (finish_arma - start_arma)/(double)CLOCKS_PER_SEC;
    cout << setiosflags(ios::showpoint | ios::uppercase);
    cout << setprecision(8) << setw(15) << "Runtime of eig_sym = " << runtime_arma << " s" << endl;

    cout << "eig_symmetric: Lambda_0 = " << eigval(0) << endl;
    cout << "eig_symmetric: Lambda_1 = " << eigval(1) << endl;
    cout << "eig_symmetric: Lambda_2 = " << eigval(2) << endl;
}
