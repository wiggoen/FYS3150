#ifndef CATCH_CONFIG_MAIN
#include <iostream>
#include <cmath>
#include "solarsystem.h"
#include "examples.h"
#include "verlet.h"
#include "euler.h"

using namespace std;

// README: https://github.com/wiggoen/FYS3150/blob/master/Project_3/README.md

int main(int numArguments, char **arguments) {
    // Default if there is no command line arguments
    //int numTimesteps = 1000;
    //double dt = 0.001;
    int numTimesteps = 1e9;
    double dt = 1e-7;
    string outputmode = "Python";
    //string outputmode = "Ovito";
    string outfilename = "Perihelion_wo_GR.txt";
    string integrator = "Verlet";
    string system = "Sun-Mercury";
    //string system = "Sun-Earth";
    int printEvery = 1;

    // If command line arguments are defined
    if (numArguments >= 2) numTimesteps = atoi(arguments[1]);
    if (numArguments >= 3) dt = atof(arguments[2]);
    if (numArguments >= 4) outputmode = string(arguments[3]);
    if (numArguments >= 5) outfilename = string(arguments[4]);
    if (numArguments >= 6) integrator = string(arguments[5]);
    if (numArguments >= 7) system = string(arguments[6]);
    if (numArguments >= 8) printEvery = atoi(arguments[7]);

    // Initialize SolarSystem
    SolarSystem solarSystem;

    // Setting numTimesteps, dt, outputmode, outfilename and integrator
    solarSystem.setNumTimesteps(numTimesteps);
    solarSystem.setDt(dt);
    solarSystem.setOutputmode(outputmode);
    solarSystem.setOutfilename(outfilename);
    solarSystem.setIntegrator(integrator);


    // Call to different systems
    if (system == "Sun-Earth") {
        examples::sun_earth(solarSystem, printEvery);
    }
    if (system == "Planet-Escape") {
        examples::planet_escape(solarSystem, printEvery);
    }
    if (system == "Sun-Mercury") {
        examples::sun_mercury(solarSystem, printEvery);
    }
    if (system == "Sun-Mercury-GR") {
        examples::sun_mercury_GR(solarSystem, printEvery);
    }
    if (system == "Sun-Earth-Jupiter") {
        examples::sun_earth_jupiter(solarSystem, printEvery);
    }
    if (system == "System-without-GR") {
        examples::system_without_GR(solarSystem, printEvery);
    }
    // Testing the runtime of the system. Does not write to file. Use with Python program 'Project_3.py'.
    if (system == "System-runtime") {
        examples::system_runtime(solarSystem);
    }

    return 0;
}

#endif
