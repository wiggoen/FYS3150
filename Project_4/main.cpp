#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "time.h"
#include "System.h"

using namespace std;


int main() //int argc, char *argv[])
{
    // Length of matrix
    int L = 2;

    // Initialize random spin matrix
    System* sys = new System(L);

    // Print state
    sys->printState();

    cout << "Energy = " << sys->computeEnergy() << endl;
    cout << "Magnetization = " << sys->computeMagnetization() << endl;

    return 0;
}

