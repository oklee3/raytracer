#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "raytracer.h"

#include "viewport.h"
#include "surface.h"
#include "surface_list.h"
#include "material.h"
#include "sphere.h"

int main() {
    surface_list world;

    // Ashen stone ground (diffuse gray)
    auto ground_material = make_shared<lambertian>(color(0.25, 0.25, 0.25));
    world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

    // Ruined spires rising from the ground (tall vertical sphere stacks)
    for (int i = -5; i <= 5; i += 2) {
        point3 base(i, 0.4, -4 + random_double(-1, 1));
        for (int j = 0; j < 3; ++j) {
            auto stone = make_shared<lambertian>(color(0.2 + 0.05*random_double(), 0.2, 0.2));
            point3 center = base + vec3(0, j * 0.6, 0);
            world.add(make_shared<sphere>(center, 0.3, stone));
        }
    }

    // Broken remnants scattered across the field
    for (int i = 0; i < 30; ++i) {
        point3 center(random_double(-10, 10), 0.2, random_double(-10, 10));
        if ((center - point3(0,0,0)).length() < 1.5) continue;

        auto rubble_material = make_shared<lambertian>(color(0.2 + 0.1*random_double(), 0.2, 0.2));
        world.add(make_shared<sphere>(center, 0.2, rubble_material));
    }

    // Rusted armor debris (random metal spheres)
    for (int i = 0; i < 10; ++i) {
        point3 center(random_double(-8, 8), 0.2, random_double(-8, 8));
        auto metal_color = color(0.4, 0.2 + 0.2*random_double(), 0.1); // dark bronze/red
        auto rusted = make_shared<metal>(metal_color, 0.5);
        world.add(make_shared<sphere>(center, 0.3, rusted));
    }

    // Central relic: floating glass orb
    auto relic_material = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, relic_material));

    // Hero’s grave marker: solid matte statue
    auto grave_material = make_shared<lambertian>(color(0.15, 0.15, 0.2));
    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, grave_material));

    // Forgotten knight’s helm: polished metal
    auto knight_helm = make_shared<metal>(color(0.8, 0.7, 0.6), 0.1);
    world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, knight_helm));

    viewport view;

    view.aspect_ratio      = 16.0 / 9.0;
    view.image_width       = 1200;
    view.samples_per_pixel = 50;
    view.max_depth         = 50;

    view.vfov     = 25;
    view.lookfrom = point3(13, 3, 6);
    view.lookat   = point3(0, 1, 0);
    view.vup      = vec3(0, 1, 0);

    view.defocus_angle = 0.2;
    view.focus_dist    = 10.0;

    view.render(world);
}