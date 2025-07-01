#ifndef SPHERE_H
#define SPHERE_H

#include "surface.h"

class sphere : public surface {
    public:
        sphere(const point3& center, double radius, shared_ptr<material> mat) 
            : center(center), radius(std::fmax(0, radius)), mat(mat) {}

        bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
            vec3 oc = center - r.origin();
            // use quadratic formula to solve for t
            auto a = r.direction().length_squared();
            auto h = dot(r.direction(), oc); // say b = -2h
            auto c = oc.length_squared() - radius * radius;

            // if discriminant < 0 then no roots, so does not intersect
            auto discriminant = h*h - a*c;
            if (discriminant < 0) {
                return false;
            }

            auto sqrtd = std::sqrt(discriminant);

            // find nearest root in acceptable t range
            auto root = (h - sqrtd) / a;
            if (!ray_t.surrounds(root)) {
                root = (h + sqrtd) / a; // if the closer root is not in range, check the other
                if (!ray_t.surrounds(root)) {
                    return false;
                }
            }

            // fill out info about the ray-sphere intersection
            rec.t = root;
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - center) / radius; // dividing by radius makes the normal unit length
            rec.set_face_normal(r, outward_normal);
            rec.mat = mat;
            return true;
        }
        
    private:
        point3 center;
        double radius;
        shared_ptr<material> mat;
};

#endif