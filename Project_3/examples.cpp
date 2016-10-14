#include "examples.h"
#include <iostream>
#include <cmath>
#include "solarsystem.h"
#include "euler.h"
#include "verlet.h"

using namespace std;

examples::examples()
{

}

int examples::sun_earth(SolarSystem &solarSystem, int printEvery) {
    bool withGr = false;
    // Sun
    CelestialBody &sun = solarSystem.createCelestialBody( vec3(0,0,0), vec3(0,0,0), 1.0, "Sun");

    // We don't need to store the reference, but just call the function without a left hand side
    // Earth
    solarSystem.createCelestialBody( vec3(1.0, 0.0, 0.0),
                                     vec3(0.0, 2*M_PI, 0),
                                     3.0e-6, "Earth");

    // To get a list (a reference, not copy) of all the bodies in the solar system, we use the .bodies() function
    vector<CelestialBody> &bodies = solarSystem.bodies();

    for(int i = 0; i < bodies.size(); i++) {
        CelestialBody &body = bodies[i]; // Reference to this body
        cout << "The position of this object is " << body.position << " with velocity " << body.velocity << endl;
    }

    solarSystem.integrate(printEvery, withGr);

    return 0;
}

int examples::planet_escape(SolarSystem &solarSystem, int printEvery) {
    bool withGr = false;
    // Sun
    CelestialBody &sun = solarSystem.createCelestialBody( vec3(0,0,0), vec3(0,0,0), 1.0, "Sun");

    // We don't need to store the reference, but just call the function without a left hand side
    // Planet
    solarSystem.createCelestialBody( vec3(1.0, 0.0, 0.0),
                                     vec3(0.0, 8.9, 0),
                                     3.0e-6, "Planet");

    // To get a list (a reference, not copy) of all the bodies in the solar system, we use the .bodies() function
    vector<CelestialBody> &bodies = solarSystem.bodies();

    for(int i = 0; i < bodies.size(); i++) {
        CelestialBody &body = bodies[i]; // Reference to this body
        cout << "The position of this object is " << body.position << " with velocity " << body.velocity << endl;
    }

    solarSystem.integrate(printEvery, withGr);

    return 0;
}

int examples::sun_mercury(SolarSystem &solarSystem, int printEvery) {
    bool withGr = false;
    // Sun
    CelestialBody &sun = solarSystem.createCelestialBody( vec3(0,0,0), vec3(0,0,0), 1.0, "Sun" );

    // We don't need to store the reference, but just call the function without a left hand side
    // Mercury
    solarSystem.createCelestialBody( vec3(-1.388351215994794E-01, 2.874076124640064E-01, 3.611730762400382E-02),
                                     vec3(-3.081033504804020E-02, -1.153752302730325E-02, 1.883146626624065E-03)*365.0,
                                     1.2e-7, "Mercury");

    // To get a list (a reference, not copy) of all the bodies in the solar system, we use the .bodies() function
    vector<CelestialBody> &bodies = solarSystem.bodies();

    for(int i = 0; i < bodies.size(); i++) {
        CelestialBody &body = bodies[i]; // Reference to this body
        cout << "The position of this object is " << body.position << " with velocity " << body.velocity << endl;
    }

    solarSystem.integrate(printEvery, withGr);

    return 0;
}

int examples::system_without_GR(SolarSystem &solarSystem, int printEvery) {
    bool withGr = false;
    // Sun
    CelestialBody &sun = solarSystem.createCelestialBody( vec3(0,0,0), vec3(0,0,0), 1.0, "Sun" );

    // We don't need to store the reference, but just call the function without a left hand side
    // Mercury
    solarSystem.createCelestialBody( vec3(-1.388351215994794E-01, 2.874076124640064E-01, 3.611730762400382E-02),
                                     vec3(-3.081033504804020E-02, -1.153752302730325E-02, 1.883146626624065E-03)*365.0,
                                     1.2e-7, "Mercury");
    // Venus
    solarSystem.createCelestialBody( vec3(2.531171709934956E-03, -7.235439738148072E-01, -1.006620932838833E-02),
                                     vec3(2.008934322426700E-02, -9.726053625259401E-05, -1.160780990531775E-03)*365.0,
                                     2.45e-6, "Venus");
    // Earth
    solarSystem.createCelestialBody( vec3(9.819128739328793E-01, 2.104822076393571E-01, -1.756137106591000E-04),
                                     vec3(-3.851159854117840E-03, 1.677807321756382E-02, -7.444403689401816E-07)*365.0,
                                     3.0e-6, "Earth");
    // Mars
    solarSystem.createCelestialBody( vec3(1.074137801923908E+00, -8.751565791508180E-01, -4.484330241084649E-02),
                                     vec3(9.406114898320066E-03, 1.202410268499505E-02, 2.097435381751857E-05)*365.0,
                                     3.3e-7, "Mars");
    // Jupiter
    solarSystem.createCelestialBody( vec3(-5.433468170028908E+00, -3.819061221110369E-01, 1.231004384238452E-01),
                                     vec3(4.425651679847022E-04, -7.171108917491057E-03, 1.992744446163222E-05)*365.0,
                                     9.5e-4, "Jupiter");
    // Saturn
    solarSystem.createCelestialBody( vec3(-2.318303159285024E+00, -9.761896118742531E+00, 2.619996914174937E-01),
                                     vec3(5.122777078109817E-03, -1.306326757884738E-03, -1.812965626845902E-04)*365.0,
                                     2.75e-4, "Saturn");
    // Uranus
    solarSystem.createCelestialBody( vec3(1.847838443295973E+01, 7.526847462019028E+00, -2.114361038013451E-01),
                                     vec3(-1.512383759608680E-03, 3.459146288519939E-03, 3.242416050249801E-05)*365.0,
                                     4.4e-5, "Uranus");
    // Neptune
    solarSystem.createCelestialBody( vec3(2.825072704568992E+01, -9.952093577677799E+00, -4.461218547546795E-01),
                                     vec3(1.022588623946866E-03, 2.979574756810357E-03, -8.514325155122657E-05)*365.0,
                                     5.15e-5, "Neptune");
    // Pluto
    solarSystem.createCelestialBody( vec3(9.393096450667111E+00, -3.182064102580347E+01, 6.879522592437006E-01),
                                     vec3(3.065499934972441E-03, 2.293283900283695E-04, -9.119583887771224E-04)*365.0,
                                     6.55e-9, "Pluto");


    // To get a list (a reference, not copy) of all the bodies in the solar system, we use the .bodies() function
    vector<CelestialBody> &bodies = solarSystem.bodies();

    for(int i = 0; i < bodies.size(); i++) {
        CelestialBody &body = bodies[i]; // Reference to this body
        cout << "The position of this object is " << body.position << " with velocity " << body.velocity << endl;
    }

    solarSystem.integrate(printEvery, withGr);

    return 0;
}

int examples::system_with_GR(SolarSystem &solarSystem, int printEvery) {
    bool withGr = true;
    // Sun
    CelestialBody &sun = solarSystem.createCelestialBody( vec3(0,0,0), vec3(0,0,0), 1.0, "Sun" );

    // We don't need to store the reference, but just call the function without a left hand side
    // Mercury
    solarSystem.createCelestialBody( vec3(-1.388351215994794E-01, 2.874076124640064E-01, 3.611730762400382E-02),
                                     vec3(-3.081033504804020E-02, -1.153752302730325E-02, 1.883146626624065E-03)*365.0,
                                     1.2e-7, "Mercury");
    // Venus
    solarSystem.createCelestialBody( vec3(2.531171709934956E-03, -7.235439738148072E-01, -1.006620932838833E-02),
                                     vec3(2.008934322426700E-02, -9.726053625259401E-05, -1.160780990531775E-03)*365.0,
                                     2.45e-6, "Venus");
    // Earth
    solarSystem.createCelestialBody( vec3(9.819128739328793E-01, 2.104822076393571E-01, -1.756137106591000E-04),
                                     vec3(-3.851159854117840E-03, 1.677807321756382E-02, -7.444403689401816E-07)*365.0,
                                     3.0e-6, "Earth");
    // Mars
    solarSystem.createCelestialBody( vec3(1.074137801923908E+00, -8.751565791508180E-01, -4.484330241084649E-02),
                                     vec3(9.406114898320066E-03, 1.202410268499505E-02, 2.097435381751857E-05)*365.0,
                                     3.3e-7, "Mars");
    // Jupiter
    solarSystem.createCelestialBody( vec3(-5.433468170028908E+00, -3.819061221110369E-01, 1.231004384238452E-01),
                                     vec3(4.425651679847022E-04, -7.171108917491057E-03, 1.992744446163222E-05)*365.0,
                                     9.5e-4, "Jupiter");
    // Saturn
    solarSystem.createCelestialBody( vec3(-2.318303159285024E+00, -9.761896118742531E+00, 2.619996914174937E-01),
                                     vec3(5.122777078109817E-03, -1.306326757884738E-03, -1.812965626845902E-04)*365.0,
                                     2.75e-4, "Saturn");
    // Uranus
    solarSystem.createCelestialBody( vec3(1.847838443295973E+01, 7.526847462019028E+00, -2.114361038013451E-01),
                                     vec3(-1.512383759608680E-03, 3.459146288519939E-03, 3.242416050249801E-05)*365.0,
                                     4.4e-5, "Uranus");
    // Neptune
    solarSystem.createCelestialBody( vec3(2.825072704568992E+01, -9.952093577677799E+00, -4.461218547546795E-01),
                                     vec3(1.022588623946866E-03, 2.979574756810357E-03, -8.514325155122657E-05)*365.0,
                                     5.15e-5, "Neptune");
    // Pluto
    solarSystem.createCelestialBody( vec3(9.393096450667111E+00, -3.182064102580347E+01, 6.879522592437006E-01),
                                     vec3(3.065499934972441E-03, 2.293283900283695E-04, -9.119583887771224E-04)*365.0,
                                     6.55e-9, "Pluto");

    // To get a list (a reference, not copy) of all the bodies in the solar system, we use the .bodies() function
    vector<CelestialBody> &bodies = solarSystem.bodies();

    for(int i = 0; i < bodies.size(); i++) {
        CelestialBody &body = bodies[i]; // Reference to this body
        cout << "The position of this object is " << body.position << " with velocity " << body.velocity << endl;
    }

    solarSystem.integrate(printEvery, withGr);

    return 0;
}
