#ifndef EXAMPLES_H
#define EXAMPLES_H
#include "solarsystem.h"

class examples
{
public:
    examples();
    static int sun_earth(SolarSystem &solarSystem, int printEvery);
    static int planet_escape(SolarSystem &solarSystem, int printEvery);
    static int sun_mercury(SolarSystem &solarSystem, int printEvery);
    static int sun_mercury_GR(SolarSystem &solarSystem, int printEvery);
    static int sun_earth_jupiter(SolarSystem &solarSystem, int printEvery);
    static int system_without_GR(SolarSystem &solarSystem, int printEvery);
    static int system_with_GR(SolarSystem &solarSystem, int printEvery);
    static int system_runtime(SolarSystem &solarSystem);
};

#endif // EXAMPLES_H


