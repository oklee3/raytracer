#ifndef MATERIAL_H
#define MATERIAL_H

#include "surface.h"

class material {
    public:
        virtual ~material() = default;

        virtual bool scatter(const ray& r, const hit_record& rec, color& attenuation, ray& scattered) const {
            return false;
        }
};

// lambertian (diffuse) reflectance
class lambertian : public material {
    public:
        // construct with albedo (some fractional reflectance)
        lambertian(const color& albedo) : albedo(albedo) {}

        bool scatter(const ray& r, const hit_record& rec, color& attenuation, ray& scattered) const override {
            vec3 scatter_direction = rec.normal + random_unit_vector();

            if (scatter_direction.near_zero()) // catch case where random vector is exactly opposite the normal
                scatter_direction = rec.normal;

            scattered = ray(rec.p, scatter_direction);
            attenuation = albedo;
            return true;
        }

    private:
        color albedo;
};

// metal reflection
class metal : public material {
    public:
        metal(const color& albedo, double fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}

        bool scatter(const ray& r, const hit_record& rec, color& attenuation, ray& scattered) const override {
            vec3 reflected = reflect(r.direction(), rec.normal);
            reflected = unit_vector(reflected) + (fuzz * random_unit_vector()); // randomly change ray direction based on fuzz
            scattered = ray(rec.p, reflected);
            attenuation = albedo;
            return (dot(scattered.direction(), rec.normal) > 0); // absorb rays that scatter below the surface
        }

    private:
        color albedo;
        double fuzz;
};

class dielectric : public material {
    public:
        dielectric(double refraction_index) : refraction_index(refraction_index) {}

        bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
            attenuation = color(1.0, 1.0, 1.0);
            double ri = rec.front_face ? (1.0 / refraction_index) : refraction_index;

            vec3 unit_direction = unit_vector(r_in.direction());
            double cos_theta = std::fmin(dot(-unit_direction, rec.normal), 1.0);
            double sin_theta = std::sqrt(1.0 - cos_theta*cos_theta);

            bool cannot_refract = ri * sin_theta > 1.0;
            vec3 direction;

            if (cannot_refract || reflectance(cos_theta, ri) > random_double())
                direction = reflect(unit_direction, rec.normal);
            else
                direction = refract(unit_direction, rec.normal, ri);

            scattered = ray(rec.p, direction);
            return true;
        }

    private:
        double refraction_index;

        static double reflectance(double cosine, double refraction_index) {
            // shlick's approximation for reflectance
            auto r0 = (1 - refraction_index) / (1 + refraction_index);
            r0 = r0*r0;
            return r0 + (1-r0) * std::pow((1-cosine), 5);
        }
};

#endif