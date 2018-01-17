#ifndef POTENTIAL_H
#define POTENTIAL_H

class Potential
{
public:
    Potential();
    double HarmonicOscillator(double rho);
    double Coulomb(double omega_r, double rho);
    double HO_2e(double omega_r, double rho);
};

#endif // POTENTIAL_H
