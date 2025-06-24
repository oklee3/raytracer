#ifndef VEC3_H
#define VEC3_h

#include <cmath>
#include <iostream>

// to store and perform operations on vectors
class vec3 {
    public:
        double x, y, z;

        vec3() {}
        vec3(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}


};

#endif