#include "solarsystem.h"
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

SolarSystem::SolarSystem() :
    m_kineticEnergy(0),
    m_potentialEnergy(0)
{
}

CelestialBody& SolarSystem::createCelestialBody(vec3 position, vec3 velocity, double mass) {
    m_bodies.push_back( CelestialBody(position, velocity, mass) );
    return m_bodies.back(); // Return reference to the newest added celstial body
}

void SolarSystem::calculateForcesAndEnergy()
{
    m_kineticEnergy = 0;
    m_potentialEnergy = 0;
    m_angularMomentum.zeros();

    for(CelestialBody &body : m_bodies) {
        // Reset forces on all bodies
        body.force.zeros();
    }

    for(int i=0; i<numberOfBodies(); i++) {
        CelestialBody &body1 = m_bodies[i];
        double dr, G;
        for(int j=i+1; j<numberOfBodies(); j++) {
            CelestialBody &body2 = m_bodies[j];
            vec3 deltaRVector = body1.position - body2.position;
            dr = deltaRVector.length();
            G = 4*M_PI*M_PI; // AU^3/(kg*yr^2)
            // Calculate the force and potential energy here
            vec3 force = G*body1.mass*body2.mass / (dr*dr) * deltaRVector.normalized();
            body1.force -= force;
            body2.force += force;
        }

        m_kineticEnergy += 0.5*body1.mass*body1.velocity.lengthSquared();
        m_potentialEnergy -= G*body1.mass/dr;
    }
}

int SolarSystem::numberOfBodies() const
{
    return m_bodies.size();
}

double SolarSystem::totalEnergy() const
{
    return m_kineticEnergy + m_potentialEnergy;
}

double SolarSystem::potentialEnergy() const
{
    return m_potentialEnergy;
}

double SolarSystem::kineticEnergy() const
{
    return m_kineticEnergy;
}

void SolarSystem::writeToFile(string filename)
{
    if(!m_file.good()) {
        m_file.open(filename.c_str(), ofstream::out);
        if(!m_file.good()) {
            cout << "Error opening file " << filename << ". Aborting!" << endl;
            terminate();
        }
    }
    //m_bodies.at(i).position

    // Choose "Ovito" or "Python" for writing to the file
    string write = "Ovito";

    if (write == "Ovito") {
        // Writing file to use with Ovito
        m_file << numberOfBodies() << endl;
        m_file << "The rows are the celestial bodies stacked, and the columns are x, y and z positions." << endl;
        for(CelestialBody &body : m_bodies) {
            m_file << "1 " << body.position.x() << " " << body.position.y() << " " << body.position.z() << "\n";
        }
    } else if (write == "python") {
        // Writing file to use with matplotlib.pyplot
        for(CelestialBody &body : m_bodies) {
            m_file << setw(25) << body.position.x() << setw(25) << body.position.y() << setw(25) << body.position.z() << "\n";
        }
    }


}

vec3 SolarSystem::angularMomentum() const
{
    return m_angularMomentum;
}

std::vector<CelestialBody> &SolarSystem::bodies()
{
    return m_bodies;
}
