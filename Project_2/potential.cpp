#include "potential.h"
#include <cmath>

Potential::Potential()
{

}
double Potential::HarmonicOscillator(double rho) {
    return rho * rho;
}
double Potential::Coulomb(double omega_r, double rho) {
    return omega_r * omega_r * rho * rho + 1.0/rho;
}
