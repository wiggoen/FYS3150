#ifndef SYSTEM_H
#define SYSTEM_H


class System
{
public:
    System(int L);
    int** init();
    double computeEnergy();
    void computeMagnetization();
    void computeHeatCapacity();
    void computeSusceptibility();
    void printState();
private:
    int m_L = 0;
    double m_Energy = 0;
    int** m_spinMatrix;
};

#endif // SYSTEM_H



