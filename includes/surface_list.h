#ifndef SURFACE_LIST_H
#define SURFACE_LIST_H

#include "surface.h"
#include <vector>

class surface_list : public surface {
    public:
        // create vector of shared pointers to surface
        // allows for automatic management of the list's reference to each object + any others
        std::vector<shared_ptr<surface>> objects;

        surface_list() {}
        surface_list(shared_ptr<surface> object) { add(object); }

        void add(shared_ptr<surface> object) {
            objects.push_back(object);
        }

        void clear() { objects.clear(); }

        bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
            hit_record temp_rec;
            bool hit_anything = false;
            auto closest_so_far = ray_t.max; // track closest in case objects overlap

            // loop thru objects, find the closest point of intersection for this ray and store in temp_rec
            for (const auto& object : objects) {
                if (object->hit(r, interval(ray_t.min, closest_so_far), temp_rec)) {
                    hit_anything = true;
                    closest_so_far = temp_rec.t;
                    rec = temp_rec; // record the closest hit point for this ray
                }
            }

            return hit_anything;
        }
};

#endif