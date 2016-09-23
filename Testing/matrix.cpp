#include <iostream>
#include <cstdlib> // use of atoi
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include "time.h"

using namespace std;

// Matrix handling
int main(int argc, char *argv[]) {
int N = 5;
double ** A;
A = new double*[N];
for (int i = 0; i < N; i++) {
    A[i] = new double[N];
}

// Initialize all elements to zero
for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
        A[i][j] = 0.0;
    }
}

// Set diagonal elements to 1
for (int i = 0; i < N; i++) {
    A[i][i] = 1.0;
}

// print out matrix
for (int i = 0; i < N; i++) {
        cout << " " << endl;
    for (int j = 0; j < N; j++) {
       cout << " " << A[i][j];
       if (i == N-1 & j == N-1) {
        cout << endl;
       }
    }
}


}