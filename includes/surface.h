#ifndef SURFACE_H
#define SURFACE_H

#include "ray.h"
#include "interval.h"

class material;

// stores information about a ray-object intersection
class hit_record {
    public:
        point3 p;
        vec3 normal;
        shared_ptr<material> mat; // allow multiple hittable objects to own one material object
        double t;
        bool front_face;

        void set_face_normal(const ray& r, const vec3& outward_normal) { // outward_normal assumed to be unit length
            // check if the ray is inside the sphere
            // if yes, reverse the normal and store info
            front_face = dot(r.direction(), outward_normal) < 0;
            normal = front_face ? outward_normal : -outward_normal;
        }
};

class surface {
    public:
        // virtual destructor to allow destruction of a surface* pointer
        virtual ~surface() = default;

        // pure virtual function, each obj class will have its own hit detection
        virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;
};

#endif