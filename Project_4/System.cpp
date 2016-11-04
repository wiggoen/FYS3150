#include "System.h"
#include "time.h"
#include <cmath>
#include <iostream>
#include <iomanip>

System::System(int L)
{
    m_L = L;
    int N = L*L;
    m_spinMatrix = init(); // Initialize random spin matrix
    Metropolis(N);
}
/*
double getMeanEnergy() {
    return m_meanEnergy;
}

double getMeanMagnetization() {
    return m_meanMagnetization;
}
*/
int **System::init()
{
    // Initialize m_spinMatrix by dynamic memory allocation
    int **m_spinMatrix = new int *[m_L];
    for (int i = 0; i < m_L; i++) {
        m_spinMatrix[i] = new int[m_L];
    }
    // Random numbers in m_spinMatrix
    for(int i = 0; i < m_L; i++) {
        for(int j = 0; j < m_L; j++) {
            //                            (condition) ? (if_true) : (if_false)
            int r = (rand()/((double)RAND_MAX)) > 0.5 ? 1 : -1;
            m_spinMatrix[i][j] = r;
        }
    }
    return m_spinMatrix;
}

void System::Metropolis(int N)
{
    double Esum = 0;
    double Msum = 0;

    double currentEnergy = computeEnergy();
    for (int i = 0; i < N; i++) {
        // Find random position
        int x = (rand()/((double)RAND_MAX))*m_L;
        int y = (rand()/((double)RAND_MAX))*m_L;

        std::cout << "- - - - - - - - - - - - - - - - - - - -" << std::endl;
        std::cout << "Current state: " << std::endl;
        printState();
        std::cout << "currentEnergy = " << currentEnergy << std::endl;
        std::cout << "Flip spin at: x = " << x << " and y = " << y << std::endl;

        // Flip a random spin
        m_spinMatrix[x][y] *= -1;

        printState();
        double newEnergy = computeEnergy();
        std::cout << "newEnergy = " << newEnergy << std::endl;

        double DeltaE = newEnergy - currentEnergy;

        std::cout << " " << std::endl;
        std::cout << "-DeltaE = " << -DeltaE << std::endl;
        std::cout << " " << std::endl;
        //std::cout << "exp(-DeltaE) = " << exp(-DeltaE) << std::endl;
        double test = (rand()/((double)RAND_MAX));

        if (DeltaE < 0) {
            std::cout << "DeltaE = " << DeltaE << " < 0" << std::endl;
        } else {
            std::cout << "DeltaE = " << DeltaE << " > 0" << std::endl;
        }
        if (test < exp(-DeltaE)) {
            std::cout << "Random = " << test << " < " << exp(-DeltaE) << " = exp(-DeltaE)" << std::endl;
        } if (test > exp(-DeltaE)) {
            std::cout << "Random = " << test << " > " << exp(-DeltaE) << " = exp(-DeltaE)" << std::endl;
        }
        std::cout << " " << std::endl;
        //std::cout << "Random: " << (rand()/((double)RAND_MAX)) << std::endl;


        // Metropolis test (accept if test fails)
        //if (!(DeltaE < 0) || !((rand()/((double)RAND_MAX)) < exp(-DeltaE)))
/*
        std::cout << "dE > 0 ? is " << (DeltaE > 0) << "  -- or --  r > exp(-dE) is : " << (test > exp(-DeltaE)) << std::endl;
        if ((DeltaE > 0) || (test > exp(-DeltaE))) // if (!(DeltaE > 0) || !(test < exp(-DeltaE)))
        {
            m_spinMatrix[x][y] *= -1;
        } else {
            currentEnergy = newEnergy;
            std::cout << "New state: " << std::endl;
            printState();
        }
*/

        std::cout << "Metropolis test:" << std::endl;
        // Metropolis test
        if (DeltaE < 0) {
            currentEnergy = newEnergy;
            std::cout << "Accepted: DeltaE < 0." << std::endl;
            printState();
            std::cout << "Current Energy = " << currentEnergy << std::endl;
        } else if (test < exp(-DeltaE)) {
            currentEnergy = newEnergy;
            std::cout << "Accepted: r < exp(-DeltaE)." << std::endl;
            printState();
            std::cout << "Current Energy = " << currentEnergy << std::endl;
        } else {
            m_spinMatrix[x][y] *= -1;
            std::cout << "Not accepted: Flipped back!" << std::endl;
            printState();
            std::cout << "Current Energy = " << currentEnergy << std::endl;
        }
        std::cout << "- - - - - - - - - - - - - - - - - - - -" << std::endl;
        std::cout << " " << std::endl;

        // Update Energy and Magnetization
        Esum += computeEnergy();
        Msum += computeMagnetization();
    }
    m_meanEnergy = Esum/N;
    m_meanMagnetization = Msum/N;
}


double System::computeEnergy() {
    double Energy = 0;
    // Loop over all spins
    for (int i = 0; i < m_L; i++) {
        for (int j = 0; j < m_L; j++) {
            //            (condition) ? (if_true) : (if_false)
            int i_previous = (i == 0) ? m_L-1 : i - 1;
            int i_next = (i == m_L-1) ? 0 : i + 1;
            int j_previous = (j == 0) ? m_L-1 : j - 1;
            int j_next = (j == m_L-1) ? 0 : j + 1;
            Energy += m_spinMatrix[i][j] * (m_spinMatrix[i_previous][j] +
                                            m_spinMatrix[i_next][j] +
                                            m_spinMatrix[i][j_previous] +
                                            m_spinMatrix[i][j_next]);
        }
    }
    return -Energy/2.0;
}


double System::computeMagnetization() {
    double Magnetization = 0;
    for (int i = 0; i < m_L; i++) {
        for (int j = 0; j < m_L; j++) {
            Magnetization += m_spinMatrix[i][j];
        }
    }
    m_Magnetization = std::abs(Magnetization);
    return m_Magnetization;
}



void System::computeHeatCapacity() {

}


void System::computeSusceptibility() {

}


void System::printState() {
    std::cout << std::endl;
    for(int i = 0; i < m_L; i++) {
        for(int j = 0; j < m_L; j++) {
            std::cout << std::setw(3) << m_spinMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

