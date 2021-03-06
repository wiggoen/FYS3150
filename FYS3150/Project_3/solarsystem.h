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
    void writeToFile_Gr(std::string filename, std::__1::string mode);
    vec3 angularMomentum() const;
    std::vector<CelestialBody> &bodies();
    void integrate(int printEvery, bool withGr);
    void setNumTimesteps(int numTimesteps);
    void setDt(double dt);
    void setOutputmode(std::string outputmode);
    void setOutfilename(std::string outfilename);
    void setIntegrator(std::string integrator);
    void calculateForcesAndEnergyGr();
    void integrate_runtime();
    void integrate_Gr(int printEvery, bool withGr);


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
    //const double m_c = 63239.7263;  // Speed of light in AU/yr
    const double m_c2 = (1.0/63239.7263)*(1.0/63239.7263); // (1/(Speed of light in AU/yr))^2
    const double m_G = 4*M_PI*M_PI; // Gravitational constant in AU^3/yr^2
    double m_l2 = 0;
};

#endif // SOLARSYSTEM_H
