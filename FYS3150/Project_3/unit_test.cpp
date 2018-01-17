//#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#ifdef CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "solarsystem.h"
#include "celestialbody.h"
#include "vec3.h"
#include "verlet.h"
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

TEST_CASE( "Conservation of angular momentum and total energy", "Approximation" )
{
    // Setting up system
    int numTimesteps = 1000;
    double dt = 0.001;
    string integrator = "Verlet";
    int printEvery = 1;
    bool withGr = false;

    // Initializing SolarSystem
    SolarSystem solarSystem;

    // Setting numTimesteps, dt and integrator
    solarSystem.setNumTimesteps(numTimesteps);
    solarSystem.setDt(dt);
    solarSystem.setIntegrator(integrator);

    // Adding celestial bodies to system
    // Sun
    solarSystem.createCelestialBody( vec3(0,0,0), vec3(0,0,0), 1.0, "Sun");

    // Earth
    solarSystem.createCelestialBody( vec3(1.0, 0.0, 0.0), vec3(0.0, 2*M_PI, 0), 3.0e-6, "Earth");


    // Integrate system
    solarSystem.integrate(printEvery, withGr);

    // Computed total energy and length of angular momentum
    double totalEnergy = solarSystem.totalEnergy();
    double LengthOfAngularMomentum = solarSystem.angularMomentum().length();

    // Analytical values for the kinetic energy, potential energy and angular momentum of the Sun-Earth system
    // Kinetic energy: K_E = 0.5*m*v**2 = 6*pi^2 * 10^(-6) = 5.922e-5
    double A_kineticEnergy = 0.5*3e-6*4*M_PI*M_PI;
    // Potential energy: P_E = -(G*M*m)/r = -12*pi^2 * 10^(-6) = -1.184e-4
    double A_potentialEnergy = -4*M_PI*M_PI*1.0*3e-6/1.0;
    // Total energy: Kinetic energy + Potential energy
    double A_totalEnergy = A_kineticEnergy + A_potentialEnergy;
    // Length of angular momentum: |l| = ||r x v|| = 2*pi
    double A_LengthOfAngularMomentum = 2*M_PI;


    // Conservation of energy
    REQUIRE(totalEnergy == Approx(A_totalEnergy));
    // Conservation of angular momentum
    REQUIRE(LengthOfAngularMomentum == Approx(A_LengthOfAngularMomentum));
}

#endif
