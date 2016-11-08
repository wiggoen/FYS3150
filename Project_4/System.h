#ifndef SYSTEM_H
#define SYSTEM_H


class System
{
public:
    System(int L, double T);
    int **init();
    void Metropolis(int N);
    double computeEnergy();
    double getMeanEnergy();
    double computeMagnetization();
    double getMeanMagnetization();
    void computeHeatCapacity();
    void computeSusceptibility();
    void printState();
    //double m_meanEnergy = 0;
    double m_meanEnergy2 = 0;
    //double m_meanMagnetization = 0;
    double m_meanMagnetization2 = 0;
private:
    int m_L = 0;
    double m_beta = 0;
    double m_Energy = 0;
    double m_Magnetization = 0;
    int** m_spinMatrix;
};

#endif // SYSTEM_H



