#ifndef INTERVAL_H
#define INTERVAL_H

#include "raytracer.h"

class interval {
    public:
        double min, max;

        interval() : min(+infinity), max(-infinity) {} // treated as an empty interval
        interval(double min, double max) : min(min), max(max) {}

        double size() const {
            return max - min;
        }

        // within or on the interval
        bool contains(double x) const {
            return min <= x && x <= max;
        }

        // strictly within the interval
        bool surrounds(double x) const {
            return min < x && x < max;
        }

        // force x to stay in bounds
        double clamp(double x) const {
            if (x < min) return min;
            if (x > max) return max;
            return x;
        }

        static const interval empty, universe;
};

// empty contains nothing, universe contains everything
const interval interval::empty = interval(+infinity, -infinity);
const interval interval::universe = interval(-infinity, +infinity);

#endif