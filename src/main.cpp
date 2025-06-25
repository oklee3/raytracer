#include "raytracer.h"

#include "viewport.h"

int main() {
    viewport view;
    view.aspect_ratio = 16.0 / 9.0;
    view.img_width = 400;

    view.render();
}