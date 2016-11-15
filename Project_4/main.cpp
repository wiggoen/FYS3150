#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <random>
//#include <mpi.h>
#include "System.h"
#include "time.h"

using namespace std;

int main(int numArguments, char **arguments) // Comment/uncomment to run different operations
{
    // Default if there is no command line arguments
    int L = 2;              // Lattice size
    double Tinitial = 1.0;  // Initial temperature
    double Tfinal = 1.0;    // Final temperature
    double Tstep = 1.0;     // Temperature step

    int mcc = 1e4;          // MonteCarloCycles

    int write_mcc= 1;      // Write Monte Carlo Cycles
    int write_average = 1; // Write mean values
    int printStatus = 1;   // Print final status

    int steadyState = 1;    // Steady state, uses 1 for every cycle
    int useMPI = 0;        // Use MPI

    string Lsize = to_string(L);
    string outfilename_average = "../Project_4/outputs/average_L"+Lsize+".txt";
    string outfilename_mcc = "../Project_4/outputs/mcc_L"+Lsize+".txt";


    // If command line arguments are defined
    if (numArguments >= 1) outfilename_average = string(arguments[1]);
    if (numArguments >= 2) outfilename_mcc = string(arguments[2]);
    if (numArguments >= 3) L = atoi(arguments[3]);
    if (numArguments >= 4) Tinitial = atof(arguments[4]);
    if (numArguments >= 5) Tfinal = atof(arguments[5]);
    if (numArguments >= 6) Tstep = atof(arguments[6]);
    if (numArguments >= 7) mcc = atoi(arguments[7]);
    if (numArguments >= 8) write_mcc = atoi(arguments[8]);
    if (numArguments >= 9) write_average = atoi(arguments[9]);
    if (numArguments >= 10) printStatus = atoi(arguments[10]);
    if (numArguments >= 11) steadyState = atoi(arguments[11]);
    if (numArguments >= 12) useMPI = atoi(arguments[12]);

    clock_t start, finish;
    start = clock();            // Start clock

    System* sys = new System(outfilename_average, outfilename_mcc, L, Tinitial,
                             Tfinal, Tstep, mcc, write_mcc, write_average, printStatus,
                             steadyState, useMPI);

    finish = clock();           // End clock

    // Time used
    double runtime = ((finish - start)/double(CLOCKS_PER_SEC));
    std::cout << std::setiosflags(std::ios::showpoint | std::ios::uppercase);
    std::cout << std::setw(15) << std::setprecision(8) << "Runtime = " << runtime << " s" << std::endl;
    std::cout << std::endl;

    return 0;
}
