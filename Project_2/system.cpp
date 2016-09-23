#include "System.h"
#include "potential.h"
#include <armadillo>
#include <cmath>

using namespace arma;

System::System(int size)
{
    N = size;
}

mat System::init(int N, double rho_max) {
    Potential* V = new Potential();

    mat A = zeros<mat>(N, N);

    double h = rho_max/N;
    double ei = 1.0/(h*h);

    for (int i = 0; i < N; i++) {
        A(i, i) = 2.0*ei + V->HarmonicOscillator((i+1)*h);
        if (i < N-1) {
            A(i, i+1) = -ei;
            A(i+1, i) = -ei;
        }
    }
    return A;
}

mat System::Jacobi_method(mat A, int N) {
    // Setting up the eigenvector matrix
    mat Z = zeros<mat>(N, N);
    for (int i = 0; i < N; i++) {
        Z(i, i) = 1.0;
    }
    int k, l;
    double epsilon = 1.0e-8;
    double max_number_iterations = (double) N * (double) N * (double) N;
    int iterations = 0;
    double max_OffDiag = maxOffDiag(A, k, l, N);

    while (fabs(max_OffDiag) > epsilon && (double) iterations < max_number_iterations) {
        max_OffDiag = maxOffDiag(A, k, l, N);
        rotate(A, Z, k, l, N);
        iterations++;
    }
    std::cout << "Number of iterations: " << iterations << "\n";
    return A;
}

double System::maxOffDiag(mat A, int &k, int &l, int N) {
    double max = 0.0;

    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (fabs(A(i, j)) > max) {
                max = fabs(A(i, j));
                l = i;
                k = j;
            }
        }
    }
    return max;
}

void System::rotate(mat &A, mat Z, int k, int l, int N) {
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

