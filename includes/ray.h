#ifndef RAY_H
#define RAY_H

class ray {
    private:
        point3 origin;
        vec3 direction;

    public:
        ray() {}
        ray(const point3& origin_, const vec3& direction_) : origin(origin_), direction(direction_) {}

        const point3& origin() const { return origin; }
        const vec3& direction() const { return direction; }

        point3 at(double t) const {
            return origin + direction * t;
        }
};       

#endif