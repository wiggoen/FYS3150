#include "potential.h"
#include <cmath>

Potential::Potential()
{

}
double Potential::HarmonicOscillator(double rho) {
    double V_HO = rho * rho;
    return V_HO;
}
double Potential::Coulomb(double omega_r, double rho) {
    double V_C = omega_r * omega_r * rho * rho + 1.0/rho;
    return V_C;
}
