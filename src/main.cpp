#include "utility.hpp"
#include "hittable.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"
#include "camera.hpp"

int main(int argc, char *argv[]) {

    hittable_list world;

    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0)); // Green
    auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5)); // Deep Blue
    auto material_left   = make_shared<metal>(color(0.8, 0.8, 0.8), 0.3);      // Silver
    auto material_right  = make_shared<metal>(color(0.8, 0.6, 0.2), 0.1);      // Gold

    world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.2),   0.5, material_center));
    world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));

    camera cam;
    cam.aspect_ratio        = 16.0 / 9.0;
    cam.image_width         = 400;
    cam.samples_per_pixels  = 100;
    cam.max_depth           = 50;
    
    cam.render(world);

    return 0;
}