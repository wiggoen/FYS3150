#ifndef SYSTEM_H
#define SYSTEM_H


class System
{
public:
    System(std::string outfilename_average, std::string outfilename_mcc, int L,
           double Tinitial, double Tfinal, double Tstep, int mcc, int write_mcc,
           int write_average, int printStatus, int steadyState, int useMPI);
    int **initialize();
    double *meanValues();
    double meanTotal();
    void computeTemperatures();
    void Metropolis();
    void runMonteCarloCycles(double &temperature);
    double computeEnergy();
    double computeMagnetization();
    int computeDeltaE(int &i, int &j);
    double *energyDifferences(double temperature);
    void printState();
    void printStatus(double &temperature);
    void output_average(double &temperature);
    void output_mcc(int &cycles, double &currentMeanEnergy, double &currentMeanMagnetization,
                    double &temperature);
private:
    int** m_spinMatrix;
    double *m_w;
    double *m_meanValues;
    int m_L;
    int m_N;
    int m_mcc;
    int m_acceptedConfigurations;
    double m_E;
    double m_M;
    double m_beta;
    double m_Tinitial;
    double m_Tfinal;
    double m_Tstep;
    int m_write_mcc;
    int m_write_average;
    int m_printStatus;
    int m_steadyState;
    int m_useMPI;
    int m_myRank;
    int m_numprocs;
    int m_numIntervals;
    int m_myLoopBegin;
    int m_myLoopEnd;
    double m_meanTotal[5];
};

#endif // SYSTEM_H

