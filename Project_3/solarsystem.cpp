#include "solarsystem.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include "verlet.h"
#include "euler.h"

using namespace std;

SolarSystem::SolarSystem() :
    m_kineticEnergy(0),
    m_potentialEnergy(0)
{
}

CelestialBody& SolarSystem::createCelestialBody(vec3 position, vec3 velocity, double mass, string name) {
    m_bodies.push_back( CelestialBody(position, velocity, mass, name) );
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
        double dr;
        for(int j=i+1; j<numberOfBodies(); j++) {
            CelestialBody &body2 = m_bodies[j];
            vec3 deltaRVector = body1.position - body2.position;
            dr = deltaRVector.length();

            // Calculate the force and potential energy here
            vec3 force = m_G*body1.mass*body2.mass / (dr*dr) * deltaRVector.normalized();
            body1.force -= force;
            body2.force += force;

            m_kineticEnergy += 0.5*body2.mass*body2.velocity.lengthSquared();
            m_potentialEnergy -= m_G*body2.mass/dr;
            m_angularMomentum += body2.position.cross(body2.velocity);
        }
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

void SolarSystem::writeToFile(string filename, string mode)
{
    if(!m_file.good()) {
        m_file.open(filename.c_str(), ofstream::out);
        if(!m_file.good()) {
            cout << "Error opening file " << filename << ". Aborting!" << endl;
            terminate();
        }
    }
    //m_bodies.at(i).position

    if (mode == "Ovito") {
        // Writing file to use with Ovito, (mode == "Ovito")
        m_file << numberOfBodies() << endl;
        m_file << "The rows are the celestial bodies stacked, and the columns are x, y and z positions." << endl;
        for(CelestialBody &body : m_bodies) {
            m_file << body.name << " " << body.position.x() << " " << body.position.y() << " " << body.position.z() << " " << body.radius() << "\n";
        }

    } else if (mode == "Python") {
        // Writing file to use with Python, (mode == "Python")
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

void SolarSystem::calculateForcesAndEnergyGr() {
    m_kineticEnergy = 0;
    m_potentialEnergy = 0;
    m_angularMomentum.zeros();

    for(CelestialBody &body : m_bodies) {
        // Reset forces on all bodies
        body.force.zeros();
    }

    for(int i=0; i<numberOfBodies(); i++) {
        CelestialBody &body1 = m_bodies[i];
        double dr;
        for(int j=i+1; j<numberOfBodies(); j++) {
            CelestialBody &body2 = m_bodies[j];
            if (body1.name == "Sun" && body2.name == "Mercury") {
                vec3 deltaRVector = body1.position - body2.position;
                dr = deltaRVector.length();

                // Calculate the force and potential energy here
                vec3 l = body2.position.cross(body2.velocity); //(1.0/body2.mass)*
                vec3 force = m_G*body1.mass*body2.mass / (dr*dr) * deltaRVector.normalized() * (1 + 3*l.lengthSquared()/(dr*dr*m_c*m_c));
                body1.force -= force;
                body2.force += force;
            } else {
                vec3 deltaRVector = body1.position - body2.position;
                dr = deltaRVector.length();

                // Calculate the force and potential energy here
                vec3 force = m_G*body1.mass*body2.mass / (dr*dr) * deltaRVector.normalized();
                body1.force -= force;
                body2.force += force;

                m_kineticEnergy += 0.5*body2.mass*body2.velocity.lengthSquared();
                m_potentialEnergy -= m_G*body2.mass/dr;
                m_angularMomentum += body2.position.cross(body2.velocity);
            }
        }
    }
}

void SolarSystem::setNumTimesteps(int numTimesteps) {
    m_numTimesteps = numTimesteps;
}

void SolarSystem::setDt(double dt) {
    m_dt = dt;
}

void SolarSystem::setOutputmode(string outputmode) {
    m_outputmode = outputmode;
}

void SolarSystem::setOutfilename(string outfilename) {
    m_outfilename = outfilename;
}

void SolarSystem::setIntegrator(string integrator) {
    m_integrator = integrator;
}

// Writing every specified timestep to file
void SolarSystem::integrate(int printEvery, bool withGr) {
    if (m_integrator == "Verlet") {
        Verlet integrator(m_dt);
        for (int i=0; i<m_numTimesteps; i++) {
            integrator.integrateOneStep(*this, withGr);
            if (i % printEvery == 0) {
                writeToFile("../Project_3/outputs/"+m_outfilename, m_outputmode);
            }
        }
    }
    if (m_integrator == "Euler") {
        Euler integrator(m_dt);
        for (int i=0; i<m_numTimesteps; i++) {
            integrator.integrateOneStep(*this, withGr);
            if (i % printEvery == 0) {
                writeToFile("../Project_3/outputs/"+m_outfilename, m_outputmode);
            }
        }
    }
    cout << "I just created my first solar system that has " << bodies().size() << " objects" << endl;
    cout << "using the " << m_integrator << " integrator and wrote to the file " << m_outfilename << " that I can read from " << m_outputmode << "." << endl;
}

// Runtime test without writing to file, testing the algorithms time usage
void SolarSystem::integrate_runtime() {
    bool withGr = false;
    if (m_integrator == "Verlet") {
        Verlet integrator(m_dt);
        for (int i=0; i<m_numTimesteps; i++) {
            integrator.integrateOneStep(*this, withGr);
        }
    }
    if (m_integrator == "Euler") {
        Euler integrator(m_dt);
        for (int i=0; i<m_numTimesteps; i++) {
            integrator.integrateOneStep(*this, withGr);
        }
    }
}
