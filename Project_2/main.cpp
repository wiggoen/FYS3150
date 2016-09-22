#include <iostream>
#include <cstdlib> // use of atoi
#include <armadillo>
#include "potential.h"
#include "System.h"

using namespace std;
using namespace arma;

int main(int argc, char *argv[])
{
    // check that we have 1 argument (number of elements N for the symmetric matrix)
    if (argc <= 1) {
        cout << "Bad usage: " << argv[0] << endl;
        cout << "You need to specify the number of N elements for the matrix in command line!" << endl;
        exit(1);
        }

    // Declaring variables
    int N = atoi(argv[1]); // first command line argument
    double rho_max = 3.0;

    System *matrA = new System();
    mat A = matrA->init(N, rho_max);
    cout << "A-matrix:" << endl;
    cout << A << endl;

    System *matrR = new System();
    mat U = matrR->Jacobi_method(A, N);
    cout << "U-matrix:" << endl;
    cout << U << endl;

    int k, l;
    System *offD = new System();
    double X = offD->maxOffDiag(A, k, l, N);
    cout << "max: " << X << endl;
    cout << "k: " << k << endl;
    cout << "l: " << l << endl;

    return 0;
}
