#include "celestialbody.h"

CelestialBody::CelestialBody(vec3 pos, vec3 vel, double mass_, std::string name_) {
    position = pos;
    velocity = vel;
    mass = mass_;
    name = name_;
}

double CelestialBody::radius()
{
    if (name=="Sun") {
        return 0.3658;
    } if (name=="Mercury") {
        return 0.086;
    } if (name=="Venus") {
        return 0.1315;
    } if (name=="Earth") {
        return 0.134;
    } if (name=="Mars") {
        return 0.1025;
    } if (name=="Jupiter") {
        return 0.254;
    } if (name=="Saturn") {
        return 0.2445;
    } if (name=="Uranus") {
        return 0.203;
    } if (name=="Neptune") {
        return 0.2015;
    } if (name=="Pluto") {
        return 0.05;
    }

    return 1.0;
}

CelestialBody::CelestialBody(double x, double y, double z, double vx, double vy, double vz, double mass_, std::string name_) {
    position = vec3(x,y,z);
    velocity = vec3(vx,vy,vz);
    mass = mass_;
    name = name_;
}

void CelestialBody::resetForce() {
    force.zeros();
}
