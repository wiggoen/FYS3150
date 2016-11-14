//    First C++ example of MPI Hello world

#include <mpi.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

ofstream ofile;

int main ()
{
    int n_spins = 2;
    int mcs = 1000;
    double dummy[5], totaldummy[5];
    string outfilename = "MPItest.txt";
    int numprocs, my_rank;
    double initial_temp, final_temp, temp_step;

    initial_temp = 1.0;
    final_temp = 2.4;
    temp_step = 0.05;

    //   MPI initializations
    //MPI_Init (&nargs, &args);
    MPI_Init (NULL, NULL);
    MPI_Comm_size (MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);
    cout << "Hello world, I have rank " << my_rank << " out of " << numprocs << endl;

    if (my_rank == 0) {
        ofile.open(outfilename);
    }

    /*
    Determine number of intervall which are used by all processes myloop_begin gives the starting point on process my_rank
    myloop_end gives the end point for summation on process my_rank
    */
    int no_intervalls = mcs/numprocs;
    int myloop_begin = my_rank*no_intervalls + 1;
    int myloop_end = (my_rank+1)*no_intervalls;
    if ( (my_rank == numprocs-1) &&( myloop_end < mcs) ) myloop_end = mcs;

    // broadcast to all nodes common variables
    MPI_Bcast (&n_spins, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast (&initial_temp, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast (&final_temp, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast (&temp_step, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    for (double temperature = initial_temp; temperature <= final_temp; temperature += temp_step)
    {
        for (int i = 0; i < 5; i++) dummy[i] = 0.0;
        for (int i = 0; i < 5; i++) totaldummy[i] = 0.0;
        for (int cycles = myloop_begin; cycles <= myloop_end; cycles++) {
            dummy[0] += 1;
            dummy[1] += 2;
            dummy[2] += 3;
            dummy[3] += 4;
            dummy[4] += 5;
        }
        for (int i = 0; i < 5; i++) {
            MPI_Reduce(&dummy[i], &totaldummy[i], 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
        }
        if (my_rank == 0) {
            ofile << setw(15) << setprecision(8) << n_spins;
            ofile << setw(15) << setprecision(8) << mcs;
            ofile << setw(15) << setprecision(8) << temperature;
            ofile << setw(15) << setprecision(8) << dummy[0];
            ofile << setw(15) << setprecision(8) << dummy[1];
            ofile << setw(15) << setprecision(8) << dummy[2];
            ofile << setw(15) << setprecision(8) << dummy[3];
            ofile << setw(15) << setprecision(8) << dummy[4];
            ofile << setw(15) << setprecision(8) << totaldummy[0];
            ofile << setw(15) << setprecision(8) << totaldummy[1];
            ofile << setw(15) << setprecision(8) << totaldummy[2];
            ofile << setw(15) << setprecision(8) << totaldummy[3];
            ofile << setw(15) << setprecision(8) << totaldummy[4] << endl;
        }
    }

    ofile.close();

    //  End MPI
    MPI_Finalize ();
    return 0;
}
