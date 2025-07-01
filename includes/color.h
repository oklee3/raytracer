#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include "interval.h"
#include <cmath>
#include <vector>

// set an alias for clarity
using color = vec3;

// Convert from linear to gamma space
inline double linear_to_gamma(double linear_component) {
    if (linear_component > 0)
        return std::sqrt(linear_component);
    return 0;
}

// Convert color to 8-bit and write into a pixel buffer
inline void write_color_to_buffer(std::vector<unsigned char>& buffer, const color& pixel_color) {
    static const interval intensity(0.000, 0.999);

    auto r = linear_to_gamma(pixel_color.x());
    auto g = linear_to_gamma(pixel_color.y());
    auto b = linear_to_gamma(pixel_color.z());

    buffer.push_back(static_cast<unsigned char>(256 * intensity.clamp(r)));
    buffer.push_back(static_cast<unsigned char>(256 * intensity.clamp(g)));
    buffer.push_back(static_cast<unsigned char>(256 * intensity.clamp(b)));
}

#endif