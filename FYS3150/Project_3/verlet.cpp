#include "verlet.h"
#include "solarsystem.h"

Verlet::Verlet(double dt) :
    m_dt(dt)
{

}


void Verlet::integrateOneStep(SolarSystem &system, bool withGr)
{
    if (withGr == false) {
        if (m_firstStep == true) {
            system.calculateForcesAndEnergy(); // F(t)
            m_firstStep = false;
        }

        for(CelestialBody &body : system.bodies()) {
            body.velocity += (body.force / body.mass) * m_dt/2.0;
            body.position += body.velocity*m_dt;

        }

        system.calculateForcesAndEnergy(); // F(t+dt)

        for(CelestialBody &body : system.bodies()) {
            body.velocity += (body.force / body.mass) * m_dt/2.0;
        }
    } else {
        if (m_firstStep == true) {
            system.calculateForcesAndEnergyGr(); // F(t)
            m_firstStep = false;
        }

        for(CelestialBody &body : system.bodies()) {
            body.velocity += (body.force / body.mass) * m_dt/2.0;
            body.position += body.velocity*m_dt;

        }

        system.calculateForcesAndEnergyGr(); // F(t+dt)

        for(CelestialBody &body : system.bodies()) {
            body.velocity += (body.force / body.mass) * m_dt/2.0;
        }
    }
}

