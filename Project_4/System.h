#ifndef SYSTEM_H
#define SYSTEM_H


class System
{
public:
    System(std::__1::string outfilename_average, std::__1::string outfilename_mcc, int L,
           double Tinitial, double Tfinal, double Tstep, int mcc, bool write_mcc,
           bool write_average, bool printStatus);
    int **initialize();
    double *meanValues();
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
    bool m_write_mcc;
    bool m_write_average;
    bool m_printStatus;
};

#endif // SYSTEM_H

