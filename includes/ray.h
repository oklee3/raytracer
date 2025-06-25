#ifndef RAY_H
#define RAY_H

class ray {
    public:
        ray() {}
        ray(const point3& origin_, const vec3& direction_) : m_origin(origin_), m_direction(direction_) {}

        const point3& origin() const { return m_origin; }
        const vec3& direction() const { return m_direction; }

        point3 at(double t) const {
            return m_origin + m_direction * t;
        }

    private:
        point3 m_origin;
        vec3 m_direction;
};       

#endif