#ifndef SYSTEM_H
#define SYSTEM_H
#include <armadillo>
#include <string>

class System
{
private:
    int N;
public:
    int k, l;
    System(int size);
    arma::mat init(double rho_max, std::string potential, double omega_r);
    void Jacobi_method(arma::mat &A, arma::mat &Z);
    double maxOffDiag(arma::mat A);
    void rotate(arma::mat &A, arma::mat &Z);
    void eig_symmetric(arma::mat &A);
};

#endif // SYSTEM_H


