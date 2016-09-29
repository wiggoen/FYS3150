#ifndef VEC3_H
#define VEC3_H
#include <iostream>


class vec3
{
public:
    double components[3];
    vec3();
    vec3(double x, double y, double z);
    double x() const { return components[0]; }
    double y() const { return components[1]; }
    double z() const { return components[2]; }
    double& operator[](int index) { return components[index]; }
    double& operator()(int index) { return components[index]; }

    vec3& operator+=(vec3 rhs);
    friend std::ostream& operator << (std::ostream& os, const vec3& myVector);
};

#endif // VEC3_H
