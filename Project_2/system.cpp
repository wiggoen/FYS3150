#include "System.h"
#include "potential.h"
#include <armadillo>
#include <cmath>

using namespace arma;

System::System()
{


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
    mat R = zeros<mat>(N, N);
    for (int i = 0; i < N; i++) {
        R(i, i) = 1.0;
    }
    return R;
}

double System::maxOffDiag(mat A, int k, int l, int N) {
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

