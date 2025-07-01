#ifndef RAYTRACER_H
#define RAYTRACER_H

// included at the top of main to autoinclude in other headers

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>

using std::make_shared;
using std::shared_ptr;

// constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.14159265358979323845;

// utility functions
inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double random_double() {
    // random double in range [0,1]
    return std::rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
    // random double in range [min,max]
    return min + (max - min) * random_double();
}

// common headers
#include "color.h"
#include "vec3.h"
#include "ray.h"
#include "interval.h"

#endif