#include <armadillo>
#ifndef SYSTEM_H
#define SYSTEM_H

class System
{
private:
    //arma::mat A;
    int N;
public:
    System(int size);
    arma::mat init(int N, double rho_max);
    arma::mat Jacobi_method(arma::mat A, int N);
    double maxOffDiag(arma::mat A, int &k, int &l, int N);
    void rotate(arma::mat &A, arma::mat Z, int k, int l, int N);
};

#endif // SYSTEM_H


