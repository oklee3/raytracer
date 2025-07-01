#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"
#include "material.h"

// camera will be initialized to default values that can be changed by calls to the instance
// initialize will be called as a part of render
class camera {
    public:
        // customizable aspects of the scene
        double aspect_ratio = 1.0;
        int image_width = 100;
        int samples_per_pixel = 10; // count of random samples for each pixel
        int max_depth = 10; // max ray bounces in a scene

        double vfov = 90; // vertical field of view
        point3 lookfrom = point3(0,0,0); // point camera is looking from
        point3 lookat = point3(0,0,-1); // point camera is looking at
        vec3 vup = vec3(0,1,0); // camera-relative up direction

        double defocus_angle = 0;
        double focus_dist = 10;

        void render(const hittable& world) {
            initialize();

            std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

            // iterate through each pixel (left to right, top to bottom)
            for (int j = 0; j < image_height; j++) {
                std::clog << "\rScanlines remaining:" << (image_height - j) << ' ' << std::flush;
                for (int i = 0; i < image_width; i++) {
                    color pixel_color(0,0,0);
                    for (int sample = 0; sample < samples_per_pixel; sample++) {
                        ray r = get_ray(i, j);
                        pixel_color += ray_color(r, max_depth, world); // add each sampled ray
                    }
                    write_color(std::cout, pixel_color * pixel_samples_scale); // average over num samples
                }
            }

            std::clog << "\rDone.                 \n";
        }

    private:
        // variables that we need to render
        int image_height;
        double pixel_samples_scale;
        point3 center;
        point3 pixel00_loc;
        vec3 pixel_delta_u;
        vec3 pixel_delta_v;
        vec3 u, v, w; // camera frame vectors
        vec3 defocus_disk_u;
        vec3 defocus_disk_v;

        void initialize() {
            image_height = int(image_width / aspect_ratio);
            image_height = (image_height < 1) ? 1 : image_height;

            pixel_samples_scale = 1.0 / samples_per_pixel;

            center = lookfrom;

            // viewport dimensions
            auto theta = degrees_to_radians(vfov);
            auto h = std::tan(theta / 2);
            auto viewport_height = 2 * h * focus_dist;
            auto viewport_width = viewport_height * (double(image_width)/image_height);

            w = unit_vector(lookfrom - lookat);
            u = unit_vector(cross(vup, w));
            v = cross(w, u);

            // viewport edge vectors
            auto viewport_u = viewport_width * u;
            auto viewport_v = viewport_height * -v;

            // pixel delta vectors (distance between pixels)
            pixel_delta_u = viewport_u / image_width; // size of one pixel along the u vector
            pixel_delta_v = viewport_v / image_height;

            // upper left pixel location
            auto viewport_upper_left = center - (focus_dist * w) - (viewport_v / 2) - (viewport_u / 2);
            pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u - pixel_delta_v); // locate the center of the upper left pixel

            // calculate camera to defocus disk basis vectors
            auto defocus_radius = focus_dist * std::tan(degrees_to_radians(defocus_angle / 2));
            defocus_disk_u = u * defocus_radius;
            defocus_disk_v = v * defocus_radius;
        }

        // create a ray from randomly sampled defocus disk point to the randomly sampled point around i, j
        ray get_ray(int i, int j) {
            // find the sampled location based on the top left pixel
            auto offset = sample_square();
            auto pixel_sample = pixel00_loc + (pixel_delta_u * (i + offset.x())) + (pixel_delta_v * (j + offset.y()));
            
            auto ray_origin = (defocus_angle <= 0) ? center : defocus_disk_sample();
            auto ray_direction = pixel_sample - ray_origin;
            return ray(ray_origin, ray_direction); // ray from camera to pixel sample
        }

        // returns vector to a random point within the unit square surrounding pixel center
        vec3 sample_square() const {
            return vec3(random_double() - 0.5, random_double() - 0.5, 0);
        }

        point3 defocus_disk_sample() {
            // return random point in the defocus disk
            auto p = random_in_unit_disk();
            return center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
        }

        color ray_color(const ray& r, int depth, const hittable& world) const {
            if (depth <= 0)
                return color(0,0,0); // return black if ray bounces max times

            hit_record rec;

            if (world.hit(r, interval(0.001, infinity), rec)) {
                ray scattered;
                color attenuation;
                if (rec.mat -> scatter(r, rec, attenuation, scattered))
                    return attenuation * ray_color(scattered, depth - 1, world); // scatter based on the material hit
                return color(0,0,0); // if the ray is absorbed
            }

            vec3 unit_direction = unit_vector(r.direction());
            // implement linear blend between blue and white
            auto a = 0.5 * (unit_direction.y() + 1.0); // converts y from [-1,1] to [0,1]
            return (1.0 - a) * color(1.0,1.0,1.0) + a * color(0.5, 0.7, 1.0);
        }   
};

#endif