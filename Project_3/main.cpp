#ifndef CATCH_CONFIG_MAIN
#include <iostream>
#include <cmath>
#include "solarsystem.h"
#include "euler.h"
#include "verlet.h"
#include "examples.h"

using namespace std;

int main(int numArguments, char **arguments) {
    // Default if there is no command line arguments
    int numTimesteps = 1000;
    double dt = 0.001;
    string outputmode = "Ovito"; // Choose "Ovito" or "Python" for writing to the file
    string outfilename = "positions.xyz";
    string integr = "Verlet";

    // If command line arguments are defined
    if (numArguments >= 2) numTimesteps = atoi(arguments[1]);
    if (numArguments >= 3) dt = atof(arguments[2]);
    if (numArguments >= 4) outputmode = string(arguments[3]);
    if (numArguments >= 5) outfilename = string(arguments[4]);
    if (numArguments >= 6) integr = string(arguments[5]);

    SolarSystem solarSystem;
    // We create new bodies like this. Note that the createCelestialBody function returns a reference to the newly created body
    // This can then be used to modify properties or print properties of the body if desired
    // Use with: solarSystem.createCelestialBody( position, velocity, mass );

    // Setting integrator, dt, outfilename and outputmode
    solarSystem.setNumTimesteps(numTimesteps);
    solarSystem.setDt(dt);
    solarSystem.setOutputmode(outputmode);
    solarSystem.setOutfilename(outfilename);
    solarSystem.setIntegrator(integr);

    //examples::newExample(&solarSystem);

    examples::earth_sun(&solarSystem);
    //examples::system_wo_mercury(numArguments, arguments);

    return 0;
}

#endif
