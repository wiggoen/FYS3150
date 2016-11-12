#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <random>
//#include <mpi.h>
#include "System.h"
#include "time.h"

using namespace std;

void opB();
void opC();
void opD();
void opE();
void opF();


int main() // Comment/uncomment to run different operations
{
    //opB();
    opC();
    //opD();
    //opE();
    //opF();

    return 0;
}


void opB() {
    string outfilename_average = "../Project_4/outputs/outfile_b_average.txt";
    string outfilename_mcc = "../Project_4/outputs/outfile_b_mcc.txt";

    int L = 2;              // Lattice size
    double Tinitial = 1.0;  // Initial temperature
    double Tfinal = 1.0;    // Final temperature
    double Tstep = 1.0;     // Temperature step

    int mcc = 1e4;          // MonteCarloCycles

    bool write_mcc= 1;      // Write Monte Carlo Cycles
    bool write_average = 1; // Write mean values
    bool printStatus = 1;   // Print final status

    // Initialize system
    System* sys = new System(outfilename_average, outfilename_mcc, L, Tinitial,
                             Tfinal, Tstep, mcc, write_mcc, write_average, printStatus);

    // Exact mean values per spin
    double exactMeanEnergyPerSpin = (-8.0*sinh(8.0)/(3.0 + cosh(8.0)))/4.0;
    double exactMeanAbsoluteMagnetizationPerSpin = ((2.0*exp(8.0) + 4.0)/(3.0 + cosh(8.0)))/4.0;

    cout << "Exact mean energy per spin = " << setprecision(8) << exactMeanEnergyPerSpin << endl;
    cout << "Exact mean absolute magnetization per spin = " << setprecision(8) << exactMeanAbsoluteMagnetizationPerSpin << endl;
    cout << endl;
}


void opC() {
    string outfilename_average = "../Project_4/outputs/outfile_c_average.txt";
    string outfilename_mcc = "../Project_4/outputs/outfile_c_mcc.txt";

    int L = 20;             // Lattice size
    double Tinitial = 1.0;  // Initial temperature
    double Tfinal = 2.4;    // Final temperature
    double Tstep = 1.4;     // Temperature step

    int mcc = 1e6;          // MonteCarloCycles

    bool write_mcc= 1;      // Write Monte Carlo Cycles
    bool write_average = 1; // Write mean values
    bool printStatus = 1;   // Print final status

    clock_t start, finish;
    start = clock();        // Start clock

    // Initialize system
    System* sys = new System(outfilename_average, outfilename_mcc, L, Tinitial,
                             Tfinal, Tstep, mcc, write_mcc, write_average, printStatus);

    finish = clock();       // End clock

    // Time used
    double runtime_opC = ((finish - start)/double(CLOCKS_PER_SEC));
    cout << setiosflags(ios::showpoint | ios::uppercase);
    cout << setprecision(8) << setw(15) << "Runtime of opC = " << runtime_opC << " s" << endl;
    cout << endl;
}


void opD() {
    string outfilename_average = "../Project_4/outputs/outfile_d_average.txt";
    string outfilename_mcc = "../Project_4/outputs/outfile_d_mcc.txt";

    int L = 20;             // Lattice size
    double Tinitial = 1.0;  // Initial temperature
    double Tfinal = 2.4;    // Final temperature
    double Tstep = 1.4;     // Temperature step

    int mcc = 1e6;          // MonteCarloCycles

    bool write_mcc= 1;      // Write Monte Carlo Cycles
    bool write_average = 1; // Write mean values
    bool printStatus = 0;   // Print final status

    // Initialize system
    System* sys = new System(outfilename_average, outfilename_mcc, L, Tinitial,
                             Tfinal, Tstep, mcc, write_mcc, write_average, printStatus);
    //sys->printState();
}


void opE() {
    string outfilename_average = "../Project_4/outputs/outfile_e_average.txt";
    string outfilename_mcc = "../Project_4/outputs/outfile_e_mcc.txt";

    int L = 20;             // Lattice size
    double Tinitial = 1.0;  // Initial temperature
    double Tfinal = 2.4;    // Final temperature
    double Tstep = 1.4;     // Temperature step

    int mcc = 1e6;          // MonteCarloCycles

    bool write_mcc= 1;      // Write Monte Carlo Cycles
    bool write_average = 1; // Write mean values
    bool printStatus = 0;   // Print final status

    // Initialize system
    System* sys = new System(outfilename_average, outfilename_mcc, L, Tinitial,
                             Tfinal, Tstep, mcc, write_mcc, write_average, printStatus);
    //sys->printState();
}


void opF() {
    string outfilename_average = "../Project_4/outputs/outfile_f_average.txt";
    string outfilename_mcc = "../Project_4/outputs/outfile_f_mcc.txt";

    int L = 20;             // Lattice size
    double Tinitial = 1.0;  // Initial temperature
    double Tfinal = 2.4;    // Final temperature
    double Tstep = 1.4;     // Temperature step

    int mcc = 1e6;          // MonteCarloCycles

    bool write_mcc= 1;      // Write Monte Carlo Cycles
    bool write_average = 1; // Write mean values
    bool printStatus = 0;   // Print final status

    // Initialize system
    System* sys = new System(outfilename_average, outfilename_mcc, L, Tinitial,
                             Tfinal, Tstep, mcc, write_mcc, write_average, printStatus);
    //sys->printState();
}
