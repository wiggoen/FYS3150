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

using namespace std;
ofstream ofile;


// Inline function for periodic boundary conditions
inline int periodic(int i, int limit, int add) {
    return (i+limit+add) % (limit);
}

// Function to read in data from screen
void read_input(int&, int&, double&, double&, double&); // default

// Function to initialise energy and magnetization
void initialize(int, double, int **, double&, double&);

// The metropolis algorithm
//void Metropolis(int, long&, int **, double&, double&, double *); // default & opB
void Metropolis(int, long&, int **, double&, double&, double *, int&); // opC

// Prints to file the results of the calculations
//void output(int, int, double, double *); // default & opB
void output(int, int, int, double *average); // opC

int main(int argc, char* argv[])
{
    char *outfilename;
    long idum;
    int **spin_matrix, n_spins, mcs;
    double w[17], average[5], E, M;

    /* -- op defalut start -- */
    //double initial_temp, final_temp, temp_step;
    /* -- op default end -- */
    //
    /* -- opB start -- */
    //n_spins = 2;
    //double temperature = 1.0;
    //int n[] = {10000, 100000, 1000000, 10000000, 100000000};
    /* -- opB end -- */
    //
    /* -- opC start -- */
    int mcs_i;
    int no_accepted = 0;
    n_spins = 20;
    double temperature = 1.0; // 1.0 and 2.4;
    mcs = 10000;
    double norm2 = 1.0/(n_spins*n_spins);  // divided by the total number of spins
    /* -- opC end -- */

    // Read in output file, abort if there are too few command-line arguments
    if( argc <= 1 ){
        cout << "Bad Usage: " << argv[0] <<
                " read also output file on same line" << endl;
        exit(1);
    }
    else{
        outfilename=argv[1];
    }
    ofile.open(outfilename);

    /* -- opC start -- */
    // Write header in output file
    ofile << setiosflags(ios::showpoint | ios::uppercase);
    ofile << "Final number of Monte Carlo trials: " << mcs << ", with temperature: " << temperature << endl;
    ofile << "     Energy:      |Magnetization|:    Number of accepted moves: " << endl;
    /* -- opC end -- */

    // Read in initial values such as size of lattice, temp and cycles
    /* -- op default start -- */
    //read_input(n_spins, mcs, initial_temp, final_temp, temp_step);
    /* -- op default end -- */

    spin_matrix = (int**) matrix(n_spins, n_spins, sizeof(int));

    /* -- op start -- */
    idum = -3; // random starting point -> default & opB: '-1' <- | -> opC: '-3' <- | //
    /* -- op end -- */
    //
    /* -- op default start -- */
    //for (double temperature = initial_temp; temperature <= final_temp; temperature+=temp_step)
    /* -- op default end -- */
    //
    /* -- opB start -- */
    //for (int j = 0; j <= 4; j++)
    /* -- opB end -- */
    //
    /* -- opC start -- */
    for (int j = 0; j < 1; j++)
        /* -- opC end -- */

    {
        cout << "loop nr: " << j << endl;
        /* -- opB start -- */
        //mcs = n[j]; // op "B"
        /* -- opB end -- */

        // initialise energy and magnetization
        E = M = 0.;

        // setup array for possible energy changes
        for( int de =-8; de <= 8; de++) w[de+8] = 0;
        for( int de =-8; de <= 8; de+=4) w[de+8] = exp(-de/temperature);

        // initialise array for expectation values
        for( int i = 0; i < 5; i++) average[i] = 0.;
        initialize(n_spins, temperature, spin_matrix, E, M);

        /* -- opC start -- */
        // Printing initial values of E and M to the result file
        ofile << setw(15) << setprecision(8) << E*norm2;
        ofile << setw(15) << setprecision(8) << fabs(M)*norm2;
        ofile << setw(15) << setprecision(8) << 0 << endl;
        /* -- opC end -- */

        // start Monte Carlo computation
        for (int cycles = 1; cycles <= mcs; cycles++){
            /* -- op default & opB start -- */
            //Metropolis(n_spins, idum, spin_matrix, E, M, w);
            /* -- op default & opB end -- */
            //
            /* -- opC start -- */
            mcs_i = cycles; // Current number of cycles.
            Metropolis(n_spins, idum, spin_matrix, E, M, w, no_accepted);
            /* -- opC end -- */

            // update expectation values
            average[0] += E;    average[1] += E*E;
            average[2] += M;    average[3] += M*M; average[4] += fabs(M);

            /* -- opC start -- */
            output(n_spins, mcs_i, no_accepted, average);
            /* -- opC end -- */
        }
        /* -- op default & opB start -- */
        // print results
        //output(n_spins, mcs, temperature, average);
        /* -- op default & opB end -- */
    }
    free_matrix((void **) spin_matrix); // free memory
    ofile.close(); // close output file
    return 0;
}


// read in input data
void read_input(int& n_spins, int& mcs, double& initial_temp,
                double& final_temp, double& temp_step)
{
    cout << "Number of Monte Carlo trials =";
    cin >> mcs;
    cout << "Lattice size or number of spins (x and y equal) =";
    cin >> n_spins;
    cout << "Initial temperature with dimension energy=";
    cin >> initial_temp;
    cout << "Final temperature with dimension energy=";
    cin >> final_temp;
    cout << "Temperature step with dimension energy=";
    cin >> temp_step;
} // end of function read_input


// function to initialise energy, spin matrix and magnetization
void initialize(int n_spins, double temperature, int **spin_matrix,
                double& E, double& M)
{
    // Setup spin matrix and intial magnetization; all spins up.
    // Commment/uncomment this section depending on use
    // Ground state configuration gives good convergence for low temperatures

    /* -- op default & opB start -- */
    // setup spin matrix and intial magnetization
    for(int y =0; y < n_spins; y++) {
        for (int x= 0; x < n_spins; x++){
            spin_matrix[y][x] = 1; // spin orientation for the ground state
            M +=  (double) spin_matrix[y][x];
        }
    }
    /* -- op default & opB end -- */

    // Setup spin matrix and intial magnetization; random start configuration.
    // Commment/uncomment this section depending on use.
    // Random spin configuration gives good convergence for high temperatures

/*
    long idum_dum = -2;
    for(int y =0; y < n_spins; y++) {
        for (int x= 0; x < n_spins; x++){
            double a = (double) ran1(&idum_dum);
            int r = 1;
            if (a < 0.5) {r = -1;}
            //cout << r;
            spin_matrix[y][x] = r; // spin orientation for the random state
            M += spin_matrix[y][x];
        }
        //cout << endl;
    }
*/

    cout << "Initial magnetization: " << M << endl;

    /* -- op default & opB start -- */
    // setup initial energy
    for(int y =0; y < n_spins; y++) {
        for (int x= 0; x < n_spins; x++){
            E -=  (double) spin_matrix[y][x]*
                    (spin_matrix[periodic(y,n_spins,-1)][x] +
                    spin_matrix[y][periodic(x,n_spins,-1)]);
        }
    }
    /* -- op default & opB end -- */
} // end function initialise

/* -- op default & opB start -- */
//void Metropolis(int n_spins, long& idum, int **spin_matrix, double& E, double&M, double *w)
/* -- op default & opB end -- */
//
/* -- opC start -- */
void Metropolis(int n_spins, long& idum, int **spin_matrix, double& E, double&M, double *w, int &acceptance)
/* -- opC end -- */
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

                /* -- opC start -- */
                acceptance += 1;
                /* -- opC end -- */
            }
        }
    }
} // end of Metropolis sampling over spins

/* -- op default & opB start -- */
//void output(int n_spins, int mcs, double temperature, double *average)
/* -- op default & opB start -- */
//
/* -- opC start -- */
void output(int n_spins, int mcs_i, int accepted, double *average)
/* -- opC end -- */
{
    /* -- op default & opB start -- */
    //double norm = 1.0/((double) (mcs));  // divided by total number of cycles
    //double norm2 = 1.0/((double) (n_spins*n_spins)); // divided by the total number of spins
    //double invT = 1.0/temperature;
    /* -- op default & opB start -- */
    //
    /* -- opB start -- */
    // Exact results for T = 1.0 (J = 1)
    //double cosh_fac = (3.0+cosh(8*invT));
    //double E_exact = -8.0*sinh(8*invT)/cosh_fac*norm2;
    //double absM_exact = (2.0*exp(8.0*invT)+4.0)/cosh_fac*norm2;
    //double Cv_exact = (8.0*invT)*(8.0*invT)*(1.0+3*cosh(8*invT))/(cosh_fac*cosh_fac)*norm2;
    //double Suscept_exact = invT*(12.0+8.0*exp(8.0*invT)+8*cosh(8.0*invT))/(cosh_fac*cosh_fac)*norm2;
    /* -- opB end -- */
    //
    /* -- op default & opB start -- */
    //double Eaverage = average[0]*norm;
    //double E2average = average[1]*norm;
    //double Maverage = average[2]*norm;
    //double M2average = average[3]*norm;
    //double Mabsaverage = average[4]*norm;
    /* -- op default & opB end -- */

    // all expectation values are per spin, divide by 1/n_spins/n_spins
    //double Evariance = (E2average- Eaverage*Eaverage)*norm2;
    //double Mvariance = (M2average - Mabsaverage*Mabsaverage)*norm2;

    /* -- op default & opB start -- */
    //ofile << setiosflags(ios::showpoint | ios::uppercase);
    /* -- op default & opB start -- */
    //
    /* -- opB start -- */
    //ofile << "Number of Monte Carlo trials: " << mcs << endl;
    //ofile << "Temperature:      Energy:      Heat capacity:  Magnetization:  Susceptibility:  abs(Magnetization):" << endl;
    /* -- opB end -- */
    //
    /* -- op default & opB start -- */
    //ofile << setw(15) << setprecision(8) << temperature;
    //ofile << setw(15) << setprecision(8) << Eaverage*norm2;
    //ofile << setw(15) << setprecision(8) << Evariance*invT*invT;
    //ofile << setw(15) << setprecision(8) << Maverage*norm2;
    //ofile << setw(15) << setprecision(8) << Mvariance*invT;
    //ofile << setw(15) << setprecision(8) << Mabsaverage*norm2 << endl;
    /* -- op default & opB start -- */
    //
    /* -- opB start -- */
    // Relative errors
    //ofile << "Diff(E):          Diff(C_V):    Diff(Chi):     Diff(abs(M)):" << endl;
    //ofile << setw(15) << setprecision(8) << abs(Eaverage*norm2-E_exact)/abs(E_exact);
    //ofile << setw(15) << setprecision(8) << abs(Evariance*invT*invT-Cv_exact)/Cv_exact;
    //ofile << setw(15) << setprecision(8) << abs(Mvariance*invT-Suscept_exact)/Suscept_exact;
    //ofile << setw(15) << setprecision(8) << abs(Mabsaverage*norm2-absM_exact)/absM_exact << endl;
    /* -- opB end -- */
    //
    /* -- opC start -- */
    double norm = 1.0/((double) (mcs_i));  // divided by total number of cycles
    double norm2 = 1.0/((double) (n_spins*n_spins)); // divided by the total number of spins
    double Eaverage = average[0]*norm;
    double Mabsaverage = average[4]*norm;
    ofile << setw(15) << setprecision(8) << Eaverage*norm2;
    ofile << setw(15) << setprecision(8) << Mabsaverage*norm2;
    ofile << setw(25) << setprecision(8) << accepted << endl;
    /* -- opC start -- */
} // end output function

