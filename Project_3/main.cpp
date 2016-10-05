#include <iostream>
#include <iomanip>
#include <armadillo>
#include <cmath>
#include <fstream>

using namespace std;
using namespace arma;

int main()//int argc, char *argv[])
{
    int N = 365;
    double h = 1.0/N; // (t_final - t_0)/N
    double pi = M_PI;

    // Position and velocity vectors
    vec x = zeros<vec>(N);
    vec y = zeros<vec>(N);
    vec v_x = zeros<vec>(N);
    vec v_y = zeros<vec>(N);

    // Initial conditions
    x(0) = 1.0; // 1 AU
    y(0) = 0.0;
    v_x(0) = -3.851159854117840E-03*365.0; // AU/yr
    v_y(0) = 1.677807321756382E-02*365.0; // AU/yr

    double r, R;
    // Eulers method
    for (int i = 0; i < N-1; i++) {
        r = sqrt(x(i)*x(i) + y(i)*y(i));
        R = r*r*r;
        cout << r << "          " << R << endl;
        v_x(i+1) = v_x(i) - h*((4*pi*pi)/R)*x(i);
        x(i+1) = x(i) + h*v_x(i);
        v_y(i+1) = v_y(i) - h*((4*pi*pi)/R)*y(i);
        y(i+1) = y(i) + h*v_y(i);
    }
    // Write to file
    ofstream ofile;
    ofile.open("../Project_3/outputs/euler.txt");
    for (int i = 0; i < N; i++) {
        ofile << setw(25) << setprecision(8) << x(i);
        ofile << setw(25) << setprecision(8) << v_x(i);
        ofile << setw(25) << setprecision(8) << y(i);
        ofile << setw(25) << setprecision(8) << v_y(i) << endl;
    }

    return 0;
}
