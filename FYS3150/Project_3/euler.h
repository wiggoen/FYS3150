#ifndef EULER_H
#define EULER_H


class Euler
{
public:
    double m_dt;
    Euler(double dt);
    void integrateOneStep(class SolarSystem &system, bool withGr);
};

#endif // EULER_H
