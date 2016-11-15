#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <mpi.h>
#include "System.h"
#include "time.h"

std::ofstream ofile1;
std::ofstream ofile2;


System::System(std::string outfilename_average, std::string outfilename_mcc, int L,
               double Tinitial, double Tfinal, double Tstep, int mcc, int write_mcc,
               int write_average, int printStatus, int steadyState, int useMPI)
{
    // Declaring private variables
    m_write_mcc = write_mcc;
    m_write_average = write_average;
    m_printStatus = printStatus;
    m_L = L;                        // Lattice size
    m_N = L*L;                      // Number of spins
    m_Tinitial = Tinitial;          // Initial temperature
    m_Tfinal = Tfinal;              // Final temperature
    m_Tstep = Tstep;                // Temperature step
    m_mcc = mcc;                    // Monte Carlo Cycles
    m_steadyState = steadyState;    // Steady state
    m_useMPI = useMPI;

    if (m_useMPI == 1) {
        // MPI initializations
        MPI_Init(NULL, NULL);
        MPI_Comm_size (MPI_COMM_WORLD, &m_numprocs);
        MPI_Comm_rank (MPI_COMM_WORLD, &m_myRank);
        if (m_myRank == 0) {
            if (m_write_mcc == 1) ofile1.open(outfilename_mcc);
            if (m_write_average == 1) ofile2.open(outfilename_average);
        }
        m_numIntervals = m_mcc/m_numprocs;              // Number of interval which are used by all processes
        m_myLoopBegin = m_myRank*m_numIntervals + 1;    // Starting point on process m_myRank
        m_myLoopEnd = (m_myRank+1)*m_numIntervals;      // End point for summation on process m_myRank
        if ((m_myRank == m_numprocs-1) && (m_myLoopEnd < m_mcc)) m_myLoopEnd = m_mcc;

        // Broadcast to all nodes common variables
        MPI_Bcast (&m_N, 1, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Bcast (&m_Tinitial, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        MPI_Bcast (&m_Tfinal, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        MPI_Bcast (&m_Tstep, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    } else {
        // Open files for writing
        if (m_write_mcc == 1) ofile1.open(outfilename_mcc);
        if (m_write_average == 1) ofile2.open(outfilename_average);
    }

    // Running system
    computeTemperatures();
}


int **System::initialize() {
    // Initialize the seed and call the Mersienne algorithm
    std::random_device rd;
    std::mt19937_64 gen(rd());
    // Set up the uniform distribution for x in [0, 1]
    std::uniform_real_distribution<double> RandomNumberGenerator(0.0, 1.0);

    // Initialize spin matrix by dynamic memory allocation
    int **m_spinMatrix = new int *[m_L];
    for (int i = 0; i < m_L; i++) {
        m_spinMatrix[i] = new int[m_L];
    }
    // Random numbers or ground state in spin matrix
    for(int i = 0; i < m_L; i++) {
        for(int j = 0; j < m_L; j++) {
            int r = (int) (RandomNumberGenerator(gen)*2);
            //                (condition) ? (if_true) : (if_false)
            m_spinMatrix[i][j] = (r == 0) ? -1 : r; // Random numbers
            //m_spinMatrix[i][j] = 1;                 // Ground state
        }
    }
    return m_spinMatrix;
}


void System::computeTemperatures() {
    for (double temperature = m_Tinitial; temperature <= m_Tfinal; temperature += m_Tstep) {
        m_E = 0.0;                                          // Initialize energy
        m_M = 0.0;                                          // Initialize magnetization
        m_w = energyDifferences(temperature);               // Set up energy differences vector
        m_meanValues = meanValues();                        // Set up mean values vector
        for (int j = 0; j < 5; j++) m_meanTotal[j] = 0.0;   // Set up mean total vector
        m_spinMatrix = initialize();                        // Initialize spin matrix
        m_E = computeEnergy();                              // Compute energy for initial state
        m_M = computeMagnetization();                       // Compute magnetization for initial state

        //std::cout << std::endl;
        //std::cout << "Initial energy = " << m_E << "  and  magnetization = " << m_M << std::endl;
        //std::cout << "Initial state:" << std::endl;
        //printState();

        m_acceptedConfigurations = 0;                       // Restarting accepted configurations
        m_beta = 1.0/temperature;                           // Computing beta
        runMonteCarloCycles(temperature);                   // Start Monte Carlo Computation

        if (m_useMPI == 1) {
            // Find total average
            for (int i = 0; i < 5; i++){
                MPI_Reduce(&m_meanValues[i], &m_meanTotal[i], 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
            }
            // Print results
            if (m_myRank == 0) {
                output_average(temperature);
            }
        } else {
            if (m_write_average == 1) {
                output_average(temperature);    // Write averages and temperatures to file
            }
        }
    }

    //std::cout << "Final energy = " << m_E << "  and  magnetization = " << m_M << std::endl;
    //std::cout << "Final state:" << std::endl;
    //printState();

    ofile1.close();  // Close output files
    ofile2.close();
    if (m_useMPI == 1) MPI_Finalize ();
}


double *System::energyDifferences(double temperature) {
    double *w = new double[17];
    // setup array for possible energy changes
    for (int de =-8; de <= 8; de++) w[de+8] = 0;
    for (int de =-8; de <= 8; de+=4) w[de+8] = exp(-de/temperature);
    return w;
}


double *System::meanValues() {
    double *m_meanValues = new double[5];            // Initialize mean values vector by static memory allocation
    for (int i = 0; i < 5; i++) m_meanValues[i] = 0.0; // Setting all mean values to zero
    return m_meanValues;
}


double System::computeEnergy() {
    double Energy = 0.0;
    // Loop over all spins
    for (int i = 0; i < m_L; i++) {
        for (int j = 0; j < m_L; j++) {
            //            (condition) ? (if_true) : (if_false)
            int i_previous = (i == 0) ? m_L-1 : i - 1;
            int i_next = (i == m_L-1) ? 0 : i + 1;
            int j_previous = (j == 0) ? m_L-1 : j - 1;
            int j_next = (j == m_L-1) ? 0 : j + 1;
            Energy += (double) m_spinMatrix[i][j] * (m_spinMatrix[i_previous][j] +
                                                     m_spinMatrix[i_next][j] +
                                                     m_spinMatrix[i][j_previous] +
                                                     m_spinMatrix[i][j_next]);
        }
    }
    return -Energy/2.0;
}


double System::computeMagnetization() {
    double Magnetization = 0.0;
    for (int i = 0; i < m_L; i++) {
        for (int j = 0; j < m_L; j++) {
            Magnetization += (double) m_spinMatrix[i][j];
        }
    }
    return Magnetization;
}


void System::runMonteCarloCycles(double &temperature) {
    if (m_useMPI == 1) {
        for (int cycles = m_myLoopBegin; cycles <= m_myLoopEnd; cycles++) {
            Metropolis(); // Run Metropolis
            // Update expectation values
            if (cycles >= m_steadyState) {
                m_meanValues[0] += m_E;
                m_meanValues[1] += m_E*m_E;
                m_meanValues[2] += m_M;
                m_meanValues[3] += m_M*m_M;
                m_meanValues[4] += std::fabs(m_M);
            }
        }
    } else {
        for (int cycles = 1; cycles <= m_mcc; cycles++) {
            Metropolis(); // Run Metropolis
            // Update expectation values
            if (cycles >= m_steadyState) {
                m_meanValues[0] += m_E;
                m_meanValues[1] += m_E*m_E;
                m_meanValues[2] += m_M;
                m_meanValues[3] += m_M*m_M;
                m_meanValues[4] += std::fabs(m_M);

                if (m_write_mcc == 1) {
                    double currentMeanEnergy = m_meanValues[0] / cycles;
                    double currentMeanMagnetization = m_meanValues[2] / cycles;
                    output_mcc(cycles, currentMeanEnergy, currentMeanMagnetization, temperature); // Write to file
                }
            }
        }
    }
}


void System::Metropolis() {
    // Initialize the seed and call the Mersienne algorithm
    std::random_device rd;
    std::mt19937_64 gen(rd());
    // Set up the uniform distribution for x in [0, 1]
    std::uniform_real_distribution<double> RandomNumberGenerator(0.0, 1.0);

    // Loop over all spins
    for (int i = 0; i < m_N; i++) {
        // Find random position
        int x = (int) (RandomNumberGenerator(gen)*m_L);
        int y = (int) (RandomNumberGenerator(gen)*m_L);

        // Compute DeltaE
        int DeltaE = computeDeltaE(x, y);

        // Metropolis test
        if (RandomNumberGenerator(gen) <= m_w[DeltaE+8]) {
            m_spinMatrix[x][y] *= -1;                // Flip one spin
            m_E += (double) DeltaE;                  // Update energy
            m_M += (double) 2.0*m_spinMatrix[x][y];  // Update magnetization
            m_acceptedConfigurations += 1;           // Accept new spin configuration
        }
    }
}


int System::computeDeltaE(int &i, int &j) {
    //            (condition) ? (if_true) : (if_false)
    int i_previous = (i == 0) ? m_L-1 : i - 1;
    int i_next = (i == m_L-1) ? 0 : i + 1;
    int j_previous = (j == 0) ? m_L-1 : j - 1;
    int j_next = (j == m_L-1) ? 0 : j + 1;
    int DeltaE = 2 * m_spinMatrix[i][j] * (m_spinMatrix[i_previous][j] +
                                           m_spinMatrix[i_next][j] +
                                           m_spinMatrix[i][j_previous] +
                                           m_spinMatrix[i][j_next]);
    return DeltaE;
}


void System::printState() // It is not recommended to print state for large lattices
{
    std::cout << std::endl;
    for(int i = 0; i < m_L; i++) {
        for(int j = 0; j < m_L; j++) {
            std::cout << std::setw(3) << m_spinMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


void System::output_mcc(int &cycles, double &currentMeanEnergy, double &currentMeanMagnetization,
                        double &temperature) {
    // All current expectation values are per spin
    double norm2 = 1.0/((double) m_N);
    ofile1 << std::setiosflags(std::ios::showpoint | std::ios::uppercase);
    ofile1 << std::setw(15) << std::setprecision(8) << temperature;
    ofile1 << std::setw(15) << std::setprecision(8) << cycles;
    ofile1 << std::setw(15) << std::setprecision(8) << m_E;
    ofile1 << std::setw(15) << std::setprecision(8) << m_M;
    ofile1 << std::setw(15) << std::setprecision(8) << fabs(m_M);
    ofile1 << std::setw(15) << std::setprecision(8) << currentMeanEnergy*norm2;
    ofile1 << std::setw(15) << std::setprecision(8) << currentMeanMagnetization*norm2;
    ofile1 << std::setw(15) << std::setprecision(8) << m_acceptedConfigurations << std::endl;
}


void System::output_average(double &temperature) {
    // Normalize expectation values
    double norm = 1.0/((double) m_mcc); // Divided by the total number of cycles
    double norm2 = 1.0/((double) m_N);  // Divided by the total number of spins
    double invT = 1.0/temperature;      // Divided by temperature

    if (m_useMPI == 1) {
        double meanTotalEnergy = m_meanTotal[0]*norm/m_numprocs;
        double meanTotalEnergy2 = m_meanTotal[1]*norm/m_numprocs;
        double meanTotalMagnetization = m_meanTotal[2]*norm/m_numprocs;
        double meanTotalMagnetization2 = m_meanTotal[3]*norm/m_numprocs;
        double meanTotalAbsMagnetization = m_meanTotal[4]*norm/m_numprocs;
        // All expectation values are per spin
        double meanTotalEnergyVariance = (meanTotalEnergy2 - meanTotalEnergy*meanTotalEnergy)*norm2;
        double meanTotalMagnetizationVariance = (meanTotalMagnetization2 - meanTotalAbsMagnetization*meanTotalAbsMagnetization)*norm2;
        // Writing to file
        ofile2 << std::setw(15) << std::setprecision(8) << m_N;
        ofile2 << std::setw(15) << std::setprecision(8) << m_mcc;
        ofile2 << std::setw(15) << std::setprecision(8) << temperature;
        ofile2 << std::setw(15) << std::setprecision(8) << meanTotalEnergy*norm2;
        ofile2 << std::setw(15) << std::setprecision(8) << meanTotalEnergy2*norm2;
        ofile2 << std::setw(15) << std::setprecision(8) << meanTotalMagnetization*norm2;
        ofile2 << std::setw(15) << std::setprecision(8) << meanTotalMagnetization2*norm2;
        ofile2 << std::setw(15) << std::setprecision(8) << meanTotalAbsMagnetization*norm2;
        ofile2 << std::setw(15) << std::setprecision(8) << meanTotalEnergyVariance*invT*invT;
        ofile2 << std::setw(15) << std::setprecision(8) << meanTotalMagnetizationVariance*invT;
        ofile2 << std::setw(15) << std::setprecision(8) << m_acceptedConfigurations << std::endl;

        if (m_printStatus == 1) {
            std::cout << std::endl;
            std::cout << "Monte Carlo Cycles = " << m_mcc << std::endl;
            std::cout << "Temperature = " << temperature << std::endl;
            std::cout << "Mean total energy per spin = " << meanTotalEnergy*norm2 << std::endl;
            std::cout << "Mean total absolute magnetization per spin = " << meanTotalAbsMagnetization*norm2 << std::endl;
            std::cout << "Mean total energy variance per spin = " << meanTotalEnergyVariance*invT*invT << std::endl;
            std::cout << "Mean total magnetization variance per spin = " << meanTotalMagnetizationVariance*invT << std::endl;
            std::cout << "Accepted configurations = " << m_acceptedConfigurations << std::endl;
            std::cout << std::endl;
        }
    } else {
        double meanEnergy = m_meanValues[0]*norm;
        double meanEnergy2 = m_meanValues[1]*norm;
        double meanMagnetization = m_meanValues[2]*norm;
        double meanMagnetization2 = m_meanValues[3]*norm;
        double meanAbsMagnetization = m_meanValues[4]*norm;
        // All expectation values are per spin
        double meanEnergyVariance = (meanEnergy2 - meanEnergy*meanEnergy)*norm2;
        double meanMagnetizationVariance = (meanMagnetization2 - meanAbsMagnetization*meanAbsMagnetization)*norm2;
        // Writing to file
        ofile2 << std::setiosflags(std::ios::showpoint | std::ios::uppercase);
        ofile2 << std::setw(15) << std::setprecision(8) << m_N;
        ofile2 << std::setw(15) << std::setprecision(8) << m_mcc;
        ofile2 << std::setw(15) << std::setprecision(8) << temperature;
        ofile2 << std::setw(15) << std::setprecision(8) << meanEnergy*norm2;
        ofile2 << std::setw(15) << std::setprecision(8) << meanEnergy2*norm2;
        ofile2 << std::setw(15) << std::setprecision(8) << meanMagnetization*norm2;
        ofile2 << std::setw(15) << std::setprecision(8) << meanMagnetization2*norm2;
        ofile2 << std::setw(15) << std::setprecision(8) << meanAbsMagnetization*norm2;
        ofile2 << std::setw(15) << std::setprecision(8) << meanEnergyVariance*invT*invT;
        ofile2 << std::setw(15) << std::setprecision(8) << meanMagnetizationVariance*invT;
        ofile2 << std::setw(15) << std::setprecision(8) << m_acceptedConfigurations << std::endl;

        if (m_printStatus == 1) {
            std::cout << std::endl;
            std::cout << "Monte Carlo Cycles = " << m_mcc << std::endl;
            std::cout << "Temperature = " << temperature << std::endl;
            std::cout << "Mean energy per spin = " << meanEnergy*norm2 << std::endl;
            std::cout << "Mean absolute magnetization per spin = " << meanAbsMagnetization*norm2 << std::endl;
            std::cout << "Mean energy variance per spin = " << meanEnergyVariance*invT*invT << std::endl;
            std::cout << "Mean magnetization variance per spin = " << meanMagnetizationVariance*invT << std::endl;
            std::cout << "Accepted configurations = " << m_acceptedConfigurations << std::endl;
            std::cout << std::endl;
        }
    }
}
