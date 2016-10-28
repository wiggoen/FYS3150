#include "System.h"
#include "time.h"
#include <iostream>
#include <iomanip>

System::System(int L)
{
    m_L = L;
    m_spinMatrix = this->init();
    m_Energy = this->computeEnergy();
}

int **System::init()
{
    // Initialize m_spinMatrix by dynamic memory allocation
    int **m_spinMatrix = new int *[m_L];
    for (int i = 0; i < m_L; i++) {
        m_spinMatrix[i] = new int[m_L];
    }

    // Initialize all m_spinMatrix elements to zero
    for(int i = 0; i < m_L; i++) {
        for(int j = 0; j < m_L; j++) {
            m_spinMatrix[i][j] = 0;
        }
    }

    // Initialize clock for random seeds
    clock_t time;
    time = clock();
    long int seed = time; // random seed
    //long int seed = 49; // static seed gives all spin down in 2x2 matrix

    // Initialize random number generator
    srand(seed);

    // Random numbers in m_spinMatrix
    for(int i = 0; i < m_L; i++) {
        for(int j = 0; j < m_L; j++) {
            //      (condition) ? (if_true) : (if_false)
            int r = (rand()/((double)RAND_MAX)) > 0.5 ? 1 : -1;
            m_spinMatrix[i][j] = r;
        }
    }
    return m_spinMatrix;
}


double System::computeEnergy() {
    int Energy = 0;
    for (int i = 0; i < m_L; i++) {
        for (int j = 0; j < m_L; j++) {
            //               (condition) ? (if_true) : (if_false)
            int i_previous = ((i == 0) ? m_L-1 : i - 1);
            int i_next = (i == m_L-1) ? 0 : i + 1;
            int j_previous = (j == 0) ? m_L-1 : j - 1;
            int j_next = (j == m_L-1) ? 0 : j + 1;
            Energy += m_spinMatrix[i][j] * (m_spinMatrix[i_previous][j] +
                                            m_spinMatrix[i_next][j] +
                                            m_spinMatrix[i][j_previous] +
                                            m_spinMatrix[i][j_next]);
        }
    }
    m_Energy = -Energy/2.0;
    return m_Energy;
}


void System::computeMagnetization() {

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
