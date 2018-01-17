#ifndef CELESTIALBODY_H
#define CELESTIALBODY_H
#include <string>
#include "vec3.h"

class CelestialBody
{
public:
    vec3 position;
    vec3 velocity;
    vec3 force;
    double mass;
    double radius();
    std::string name;

    CelestialBody(vec3 position, vec3 velocity, double mass, std::string name="noname");
    CelestialBody(double x, double y, double z, double vx, double vy, double vz, double mass, std::string name="noname");
    void resetForce();
};

#endif // CELESTIALBODY_H
