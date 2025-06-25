#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "vec3.h"
#include <iostream>

class viewport {
    public:
        double aspect_ratio;
        int img_width;

        void render() {
            initialize();

            for (int i = 0; i < img_height; i++) {
                for (int j = 0; j < img_width; j++) {
                    // compute colors for each pixel
                }
            }
        }

    private:
        int img_height;
        point3 camera_center;
        point3 topleft_pixel;
        vec3 pixel_delta_x;
        vec3 pixel_delta_y;

        void initialize() {
            img_height = int(img_width / aspect_ratio);
            camera_center = point3(0,0,0);

            // set to default values
            auto focal_length = 1.0;
            auto viewport_height = 2.0;
            auto viewport_width = viewport_height * aspect_ratio;

            // calculate values to help find pixel centers
            auto viewport_x = vec3(viewport_width, 0, 0);
            auto viewport_y = vec3(0, -viewport_height, 0); // assume -y goes down img
            auto pixel_delta_x = viewport_x / img_width;
            auto pixel_delta_y = viewport_y / img_height;

            point3 viewport_top_left = camera_center - vec3(0,0,focal_length) - (viewport_x / 2) - (viewport_y / 2);
            topleft_pixel = viewport_top_left - 0.5 * (pixel_delta_x - pixel_delta_y);
        }
};

#endif