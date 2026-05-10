#include <scenes.hpp>
#include <sphere.hpp>
#include <hittable_list.hpp>
#include <material.hpp>
#include <utility.hpp>
#include <stdexcept>
#include <bvh.hpp>
#include <memory>


namespace {

    void final_scene(hittable_list &world, camera &cam, bool bouncing) {

        auto ground_material = std::make_shared<lambertian>(color(0.5, 0.5, 0.5));
        world.add(std::make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

        for (int a = -11; a < 11; a++) {
            for (int b = -11; b < 11; b++) {
                auto choose_mat = random_double();
                point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

                if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                    std::shared_ptr<material> sphere_material;

                    if (choose_mat < 0.8) {
                        // diffuse
                        auto albedo = color::random() * color::random();
                        sphere_material = std::make_shared<lambertian>(albedo);
                        
                        if(bouncing) {
                            auto center2 = center + vec3(0, random_double(0,.5), 0);
                            world.add(std::make_shared<sphere>(center, center2, 0.2, sphere_material));
                        } else {
                            world.add(std::make_shared<sphere>(center, 0.2, sphere_material));
                        }
                    } else if (choose_mat < 0.95) {
                        // metal
                        auto albedo = color::random(0.5, 1);
                        auto fuzz = random_double(0, 0.5);
                        sphere_material = std::make_shared<metal>(albedo, fuzz);
                        world.add(std::make_shared<sphere>(center, 0.2, sphere_material));
                    } else {
                        // glass
                        sphere_material = std::make_shared<dielectric>(1.5);
                        world.add(std::make_shared<sphere>(center, 0.2, sphere_material));
                    }
                }
            }
        }

        auto material1 = std::make_shared<dielectric>(1.5);
        world.add(std::make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

        auto material2 = std::make_shared<lambertian>(color(0.4, 0.2, 0.1));
        world.add(std::make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

        auto material3 = std::make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
        world.add(std::make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

        cam.aspect_ratio = 16.0 / 9.0;
        cam.image_width = bouncing ? 400: 1200;
        cam.samples_per_pixel = bouncing ? 100: 500;
        cam.max_depth = 50;

        cam.vfov = 20;
        cam.lookfrom = point3(13, 2, 3);
        cam.lookat = point3(0, 0, 0);
        cam.vup = vec3(0, 1, 0);

        cam.defocus_angle = 0.6;
        cam.focus_dist = 10.0;
    }

    void macro_marbles(hittable_list &world, camera &cam) {
        auto mat_ground = std::make_shared<lambertian>(color(0.1, 0.1, 0.1)); // Dark floor
        world.add(std::make_shared<sphere>(point3(0, -1000, 0), 1000, mat_ground));

        // Create a tight cluster of small spheres
        for (int a = -5; a < 5; a++) {
            for (int b = -5; b < 5; b++) {
                auto choose_mat = random_double();
                point3 center(a * 0.4 + random_double(0, 0.1), 0.1, b * 0.4 + random_double(0, 0.1));

                if ((center - point3(0, 0.1, 0)).length() > 0.3) {
                    if (choose_mat < 0.5) {
                        auto albedo = color::random(0.1, 0.9);
                        world.add(std::make_shared<sphere>(center, 0.1, std::make_shared<lambertian>(albedo)));
                    } else if (choose_mat < 0.8) {
                        auto albedo = color::random(0.5, 1);
                        world.add(std::make_shared<sphere>(center, 0.1, std::make_shared<metal>(albedo, 0.1)));
                    } else {
                        world.add(std::make_shared<sphere>(center, 0.1, std::make_shared<dielectric>(1.5)));
                    }
                }
            }
        }

        auto focal_metal = std::make_shared<metal>(color(0.9, 0.2, 0.1), 0.05); // Bright red metal
        world.add(std::make_shared<sphere>(point3(0, 0.3, 0), 0.3, focal_metal));

        cam.aspect_ratio = 16.0 / 9.0;
        cam.image_width = 800;
        cam.samples_per_pixel = 100;
        cam.max_depth = 50;

        cam.vfov = 20;
        cam.lookfrom = point3(2, 1.5, 3);
        cam.lookat = point3(0, 0.3, 0); // Looking exactly at the red marble
        cam.vup = vec3(0, 1, 0);

        cam.defocus_angle = 3.0;                               // Aggressive blur
        cam.focus_dist = (cam.lookfrom - cam.lookat).length(); // Math to perfectly focus on the target
    }
}


Scene make_scene(int scene_id) {
    Scene scene;
    scene.id = scene_id;

    switch (scene_id) {

        case 1:
            scene.name = "final_scene";
            final_scene(scene.world, scene.cam, false);
            break;

        case 2:
            scene.name = "macro_marbles";
            macro_marbles(scene.world, scene.cam);
            break;

        default:
            throw std::runtime_error("Invalid scene id: " + std::to_string(scene_id));
    }
    
    scene.world = hittable_list(std::make_shared<bvh_node>(scene.world));

    return scene;
}
