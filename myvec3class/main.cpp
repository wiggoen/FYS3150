#include <iostream>
#include "vec3.h"

using namespace std;

int main(int argc, char *argv[])
{
    vec3 a(1, 1, 1);
    vec3 b = a;
    cout << b << endl;
    a += b;

    cout << a << endl;
    // vec3 = a + b;

    //cout << "Hello World!" << endl;
    return 0;
}
