#include "vec3.h"

vec3::vec3()
{
    components[0] = 0;
    components[1] = 0;
    components[2] = 0;
}

vec3::vec3(double x, double y, double z)
{
    components[0] = x;
    components[1] = y;
    components[2] = z;
}

vec3 &vec3::operator+=(vec3 rhs)
{
    components[0] += rhs[0];
    components[1] += rhs[1];
    components[2] += rhs[2];

    return *this;
}
std::ostream &operator << (std::ostream& os, const vec3& myVector)
{
    os << "[" << myVector.x() << ", " << myVector.y() << ", " << myVector.z() << "]";
    return os;
}
