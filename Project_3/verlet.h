#ifndef VERLET_H
#define VERLET_H


class Verlet
{
public:
    double m_dt;
    Verlet(double dt);
    void integrateOneStep(class SolarSystem &system);
private:
    bool m_firstStep = true;
};

#endif // VERLET_H

