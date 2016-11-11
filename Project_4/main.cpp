/*
   Program to solve the two-dimensional Ising model
   with zero external field.
   The coupling constant J = 1
   Boltzmann's constant = 1, temperature has thus dimension energy
   Metropolis sampling is used. Periodic boundary conditions.
*/

#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "lib.h"

using namespace  std;

ofstream ofile;
ofstream ofile2;

// Inline function for periodic boundary conditions
inline int periodic(int i, int limit, int add) {
    return (i+limit+add) % (limit);
}

// Calculate different quantities
void opB(string&, string&, int&, int&, double&, double&, double&, bool&, bool&);

// Function to read in data from screen
//void read_input(int&, int&, double&, double&, double&);

// Function to initialise energy and magnetization
void initialize(int, double, int **, double&, double&);

//
void computeTemperature(long&, int&, int&, double&, double&, double&, bool&, bool&);

// The metropolis algorithm
void Metropolis(int, long&, int **, double&, double&, double *);

// Prints to file the results of the calculations
void output(int, int, double, double *);
void output_states(int, int, int, double &, double &);

int main()//int argc, char* argv[])
{
    //char *outfilename;
    string outfilename;
    string outfilename_states;
    long idum;
    // int **spin_matrix
    int n_spins, mcs;
    // double w[17], average[5];
    double initial_temp, final_temp, E, M, temp_step;
    bool write_mcs, write_temp;

    // Choose operation
    opB(outfilename, outfilename_states, n_spins, mcs, initial_temp, final_temp,
        temp_step, write_mcs, write_temp);
    //opC();
    //opD();
    //opE();
    //opF();

    ofile.open(outfilename);
    ofile2.open(outfilename_states);

    idum = -1; // random starting point

    computeTemperature(idum, n_spins, mcs, initial_temp, final_temp,
                       temp_step, write_mcs, write_temp);

    return 0;
}

void opB(string& outfilename, string& outfilename_states, int& n_spins,
         int& mcs, double& initial_temp, double& final_temp,
         double& temp_step, bool& write_mcs, bool& write_temp) {
    outfilename = "../Project_4/outputs/outfile_b_temp.txt";     // output file
    outfilename_states = "../Project_4/outputs/outfile_b_states.txt";
    n_spins = 2;        // Lattice size or number of spins (x and y equal)
    mcs = 1e5;          // Number of Monte Carlo trials
    initial_temp = 1.0; // Initial temperature with dimension energy
    final_temp = 1.0;   // Final temperature with dimension energy
    temp_step = 1.0;    // Temperature step with dimension energy
    write_mcs = 1;
    write_temp = 1;
}


void computeTemperature(long& idum, int& n_spins, int& mcs, double& initial_temp,
                        double& final_temp, double& temp_step, bool& write_mcs,
                        bool& write_temp)
{
    // Declaration
    int **spin_matrix;
    double w[17], average[5], E, M;

    spin_matrix = (int**) matrix(n_spins, n_spins, sizeof(int));

    for (double temperature = initial_temp; temperature <= final_temp; temperature+=temp_step){
        //    initialise energy and magnetization
        E = M = 0.0;
        // setup array for possible energy changes
        for (int de =-8; de <= 8; de++) w[de+8] = 0;
        for (int de =-8; de <= 8; de+=4) w[de+8] = exp(-de/temperature);
        // initialize array for expectation values
        for (int i = 0; i < 5; i++) average[i] = 0.0;

        // initialize state
        initialize(n_spins, temperature, spin_matrix, E, M);

        if (write_mcs == 1) {
            // first state
            output_states(n_spins, mcs, 0, E, M);
        }


        // start Monte Carlo computation
        for (int cycles = 1; cycles <= mcs; cycles++){
            Metropolis(n_spins, idum, spin_matrix, E, M, w);
            // update expectation values
            average[0] += E;    average[1] += E*E;
            average[2] += M;    average[3] += M*M;    average[4] += fabs(M);
            // print results for mcs
            if (write_mcs == 1) {
                // for every state
                output_states(n_spins, mcs, cycles, E, M);
            }
        }
        // print results
        if (write_temp == 1) {
            // averages and temperature
            output(n_spins, mcs, temperature, average);
        }

    }
    free_matrix((void **) spin_matrix); // free memory
    ofile.close();  // close output file
    ofile2.close();
}


// function to initialize energy, spin matrix and magnetization
void initialize(int n_spins, double temperature, int **spin_matrix, double& E, double& M)
{
    // setup spin matrix and intial magnetization
    for(int y =0; y < n_spins; y++) {
        for (int x= 0; x < n_spins; x++){
            spin_matrix[y][x] = 1; // spin orientation for the ground state
            M +=  (double) spin_matrix[y][x];
        }
    }
    // setup initial energy
    for(int y =0; y < n_spins; y++) {
        for (int x= 0; x < n_spins; x++){
            E -=  (double) spin_matrix[y][x]*
                    (spin_matrix[periodic(y,n_spins,-1)][x] +
                    spin_matrix[y][periodic(x,n_spins,-1)]);
        }
    }
} // end function initialise

void Metropolis(int n_spins, long& idum, int **spin_matrix, double& E,
                double&M, double *w)
{
    // loop over all spins
    for(int y =0; y < n_spins; y++) {
        for (int x= 0; x < n_spins; x++){
            int ix = (int) (ran1(&idum)*(double)n_spins);
            int iy = (int) (ran1(&idum)*(double)n_spins);
            int deltaE =  2*spin_matrix[iy][ix]*
                    (spin_matrix[iy][periodic(ix,n_spins,-1)]+
                    spin_matrix[periodic(iy,n_spins,-1)][ix] +
                    spin_matrix[iy][periodic(ix,n_spins,1)] +
                    spin_matrix[periodic(iy,n_spins,1)][ix]);
            if ( ran1(&idum) <= w[deltaE+8] ) {
                spin_matrix[iy][ix] *= -1;  // flip one spin and accept new spin config
                M += (double) 2*spin_matrix[iy][ix];
                E += (double) deltaE;
            }
        }
    }
} // end of Metropolis sampling over spins


void output(int n_spins, int mcs, double temperature, double *average)
{
    // All average values are normalized
    double norm = 1.0/((double) (mcs)); // divided by total number of cycles
    double Eaverage = average[0]*norm;
    double E2average = average[1]*norm;
    double Maverage = average[2]*norm;
    double M2average = average[3]*norm;
    double Mabsaverage = average[4]*norm;
    // All expectation values are per spin
    double norm2 = 1.0/((double) (n_spins*n_spins)); // divided by 1/n_spins/n_spins
    double invT = 1.0/temperature; // inverse temperature
    double Evariance = (E2average- Eaverage*Eaverage)*norm2;
    double Mvariance = (M2average - Mabsaverage*Mabsaverage)*norm2;
    // Write to file
    ofile << setiosflags(ios::showpoint | ios::uppercase);
    ofile << setw(15) << setprecision(8) << temperature;
    ofile << setw(15) << setprecision(8) << Eaverage*norm2;
    ofile << setw(15) << setprecision(8) << Evariance*invT*invT;
    ofile << setw(15) << setprecision(8) << Maverage*norm2;
    ofile << setw(15) << setprecision(8) << Mvariance*invT;
    ofile << setw(15) << setprecision(8) << Mabsaverage*norm2 << endl;
} // end output function

void output_states(int n_spins, int mcs, int cycles, double &E, double &M)
{
    // All average values are normalized
    double norm = 1.0/((double) (mcs)); // divided by total number of cycles
    //double Eaverage = average[0]*norm;
    //double E2average = average[1]*norm;
    //double Maverage = average[2]*norm;
    //double M2average = average[3]*norm;
    //double Mabsaverage = average[4]*norm;
    // All expectation values are per spin
    double norm2 = 1.0/((double) (n_spins*n_spins)); // divided by 1/n_spins/n_spins
    //double invT = 1.0/temperature; // inverse temperature
    //double Evariance = (E2average- Eaverage*Eaverage)*norm2;
    //double Mvariance = (M2average - Mabsaverage*Mabsaverage)*norm2;
    // Write to file
    ofile2 << setiosflags(ios::showpoint | ios::uppercase);
    //ofile2 << setw(15) << setprecision(8) << temperature;
    //ofile2 << setw(15) << setprecision(8) << mcs;
    ofile2 << setw(15) << setprecision(8) << cycles;
    ofile2 << setw(15) << setprecision(8) << E;
    //ofile2 << setw(15) << setprecision(8) << Evariance*invT*invT;
    ofile2 << setw(15) << setprecision(8) << M;
    //ofile2 << setw(15) << setprecision(8) << Mvariance*invT;
    ofile2 << setw(15) << setprecision(8) << fabs(M) << endl;
} // end output function




