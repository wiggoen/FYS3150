#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "time.h"
#include "System.h"
//#include <mpi.h>

using namespace std;


int main() //int argc, char *argv[])
{

    clock_t time; // Initialize clock for random seeds
    time = clock();
    long int seed = time; // random seed
//    long int seed = 49; // static seed gives all spin down in 2x2 matrix
    srand(seed); // Initialize random number generator

    int L = 2; // Length of matrix

    System* sys = new System(L); // Initialize random spin matrix

    // Print state
//    sys->printState();
/*
    cout << "Energy = " << sys->computeEnergy() << endl;
    cout << "Expected Energy = " << sys->expectedEnergy(10000) << endl;
    cout << " " << endl;
    cout << "Magnetization = " << sys->computeMagnetization() << endl;
    cout << "Expected Magnetization = " << sys->expectedMagnetization(10000) << endl;
    cout << " " << endl;
*/
    return 0;
}

