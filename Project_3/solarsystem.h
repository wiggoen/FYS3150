#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H

#include "celestialbody.h"
#include <vector>
#include <string>
#include <fstream>
#include <cmath>

class SolarSystem
{
public:
    SolarSystem();
    CelestialBody &createCelestialBody(vec3 position, vec3 velocity, double mass, std::string name = "noname");
    void calculateForcesAndEnergy();
    int numberOfBodies() const;
    double totalEnergy() const;
    double potentialEnergy() const;
    double kineticEnergy() const;
    void writeToFile(std::string filename, std::__1::string mode);
    vec3 angularMomentum() const;
    std::vector<CelestialBody> &bodies();
    void integrate(int printEvery, bool withGr);
    void setNumTimesteps(int numTimesteps);
    void setDt(double dt);
    void setOutputmode(std::string outputmode);
    void setOutfilename(std::string outfilename);
    void setIntegrator(std::string integrator);
    void calculateForcesAndEnergyGr();


private:
    std::vector<CelestialBody> m_bodies;
    vec3 m_angularMomentum;
    std::ofstream m_file;
    double m_kineticEnergy;
    double m_potentialEnergy;
    int m_numTimesteps;
    double m_dt;
    std::string m_outputmode;
    std::string m_outfilename;
    std::string m_integrator;
    const double m_c = 63239.7263; // AU/yr
    const double m_G = 4*M_PI*M_PI; // AU^3/(kg*yr^2)
};

#endif // SOLARSYSTEM_H
