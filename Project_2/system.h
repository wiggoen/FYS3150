#include <armadillo>
#include <string>
#ifndef SYSTEM_H
#define SYSTEM_H

class System
{
private:
    //arma::mat A;
    int N;
public:
    int k, l;
    System(int size);
    arma::mat init(double rho_max, std::string potential, double omega_r);
    void Jacobi_method(arma::mat &A, arma::mat &Z);
    double maxOffDiag(arma::mat A);
    void rotate(arma::mat &A, arma::mat &Z);
    //int FindLowestIndex(arma::mat &A);
};

#endif // SYSTEM_H


