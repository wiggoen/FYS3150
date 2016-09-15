#include <iostream>
#include <cstdlib> // use of atoi
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include "time.h"

using namespace std;
ofstream ofile;

void gen_solve(int N, double* v) {
    // Start gen_solve
    // Declaration of variables
    double *a = new double[N+2];
    double *b = new double[N+2];
    double *b_tilde = new double[N+2];
    double *c = new double[N+2];
    double *f = new double[N+2];
    double *f_tilde = new double[N+2];
    double *x = new double[N+2];
    double h = 1.0/(N+1);

    // Initialize elements
    for (int i = 0; i < N+2; i++) {
        a[i] = -1.0;
        b[i] = 2.0;
        c[i] = -1.0;
        x[i] = i*h;
        f[i] = pow(h, 2)*100*exp(-10*x[i]);
        v[i] = 0.0;
    }

    // Initial conditions
    f_tilde[1] = f[1];
    b_tilde[1] = b[1];

    // Decomposition and forward substitution
    for (int i = 2; i < N+1; i++) {
        b_tilde[i] = b[i] - a[i-1]*c[i-1]/b_tilde[i-1]; // new diagonal elements
        f_tilde[i] = f[i] - (a[i-1]*f_tilde[i-1])/b_tilde[i-1];
    }
    v[N] = f_tilde[N]/b_tilde[N];

    // Backward substitution
    for (int i = N-1; i >= 1; i--) {
        v[i] = (f_tilde[i]-c[i]*v[i+1])/b_tilde[i];
    }
}   // End gen_solve

void special_solve(int N, double* v) {
    // Start special_solve
    double *b = new double[N+2];
    double *b_tilde = new double[N+2];
    double *f = new double[N+2];
    double *f_tilde = new double[N+2];
    double *x = new double[N+2];
    double *z = new double[N+2];
    double h = 1.0/(N+1);

    // initialize elements
    for (int i = 0; i < N+2; i++) {
        b[i] = 2.0;
        x[i] = i*h;
        f[i] = pow(h, 2)*100*exp(-10*x[i]);
        v[i] = 0.0;
    }
    // Initial conditions
    f_tilde[1] = f[1];
    b_tilde[1] = b[1];

    // decomposition and forward substitution
    for (int i = 2; i < N+1; i++) {
        z[i] = (i-1.0)/i;
        b_tilde[i] = (i+1.0)/i; // new diagonal elements, 1.0 to avoid integer division
        f_tilde[i] = f[i] - z[i]*f[i-1];
    }
    v[N] = f_tilde[N]/b_tilde[N];

    // backward substitution
    for (int i = N-1; i >= 1; i--) {
        v[i-1] = z[i]*(f_tilde[i-1]-v[i]);
    }
}   // End special_solve

int main(int argc, char* argv[])
{
    // check that we have 2 arguments (file name and number of elements in vector)
    if (argc <= 2) {
        cout << "Bad usage: " << argv[0] << endl;
        cout << "You need to specify the out file name and the number of N elements for the vector in command line!" << endl;
        exit(1);
    }

    // Declaring variables
    string outfilename = string(argv[1]) + "-" + string(argv[2]) + ".txt"; // first command line argument
    int N = atoi(argv[2]); // second command line argument
    double* v = new double[N];
    clock_t start, finish;

    // Start clock
    start = clock();

    // Call solver
    gen_solve(N,v);

    finish = clock();
    // End clock

    double timeused = ((finish - start)/double(CLOCKS_PER_SEC));
    cout << setiosflags(ios::showpoint | ios::uppercase);
    cout << setprecision(10) << setw(20) << "Time used = " << timeused << endl;


    // open file and write results to file
    ofile.open(outfilename);
    for (int i = 0; i < N+2; i++) {
        ofile << setw(15) << setprecision(8) << v[i] << endl;
    }
    ofile.close();

    return 0;
}
