#include <scenes.hpp>
#include <sphere.hpp>
#include <hittable_list.hpp>
#include <material.hpp>
#include <utility.hpp>
#include <stdexcept>
#include <memory>


namespace {

    void wide_angle_of_view(hittable_list &world, camera &cam) {
        auto R = std::cos(pi / 4);

        auto material_left = std::make_shared<lambertian>(color(0, 0, 1));
        auto material_right = std::make_shared<lambertian>(color(1, 0, 0));

        world.add(std::make_shared<sphere>(point3(-R, 0, -1), R, material_left));
        world.add(std::make_shared<sphere>(point3(R, 0, -1), R, material_right));

        cam.aspect_ratio = 16.0 / 9.0;
        cam.image_width = 400;
        cam.samples_per_pixel = 100;
        cam.max_depth = 50;

        cam.vfov = 90;
    }
    void hallow_glass_sphere(hittable_list &world, camera &cam) {
        auto material_ground = std::make_shared<lambertian>(color(0.8, 0.8, 0.0));
        auto material_center = std::make_shared<lambertian>(color(0.1, 0.2, 0.5));
        auto material_left = std::make_shared<dielectric>(1.50);
        auto material_bubble = std::make_shared<dielectric>(1.00 / 1.50);
        auto material_right = std::make_shared<metal>(color(0.8, 0.6, 0.2), 0.0);

        world.add(std::make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
        world.add(std::make_shared<sphere>(point3(0.0, 0.0, -1.2), 0.5, material_center));
        world.add(std::make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
        world.add(std::make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.4, material_bubble));
        world.add(std::make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));

        cam.aspect_ratio = 16.0 / 9.0;
        cam.image_width = 400;
        cam.samples_per_pixel = 100;
        cam.max_depth = 50;
    }

    void spheres_with_depth_of_field(hittable_list &world, camera &cam) {
        auto material_ground = std::make_shared<lambertian>(color(0.8, 0.8, 0.0));
        auto material_center = std::make_shared<lambertian>(color(0.1, 0.2, 0.5));
        auto material_left = std::make_shared<dielectric>(1.50);
        auto material_bubble = std::make_shared<dielectric>(1.00 / 1.50);
        auto material_right = std::make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);

        world.add(std::make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
        world.add(std::make_shared<sphere>(point3(0.0, 0.0, -1.2), 0.5, material_center));
        world.add(std::make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
        world.add(std::make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.4, material_bubble));
        world.add(std::make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));

        cam.aspect_ratio = 16.0 / 9.0;
        cam.image_width = 400;
        cam.samples_per_pixel = 100;
        cam.max_depth = 50;

        cam.vfov = 20;
        cam.lookfrom = point3(-2, 2, 1);
        cam.lookat = point3(0, 0, -1);
        cam.vup = vec3(0, 1, 0);

        cam.defocus_angle = 10.0;
        cam.focus_dist = 3.4;
    }

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
                        world.add(std::make_shared<sphere>(center, 0.2, sphere_material));

                        if(bouncing) {
                            auto center2 = center + vec3(0, random_double(0,.5), 0);
                            world.add(std::make_shared<sphere>(center, center2, 0.2, sphere_material));
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

    void sphere_room(hittable_list &world, camera &cam) {
        // Huge spheres acting as flat walls/floor/ceiling
        auto mat_floor = std::make_shared<lambertian>(color(0.8, 0.8, 0.8));
        auto mat_ceiling = std::make_shared<lambertian>(color(0.8, 0.8, 0.8));
        auto mat_back = std::make_shared<lambertian>(color(0.8, 0.8, 0.8));
        auto mat_left = std::make_shared<lambertian>(color(0.8, 0.1, 0.1));  // Red wall
        auto mat_right = std::make_shared<lambertian>(color(0.1, 0.8, 0.1)); // Green wall

        const double R = 100000.0;

        // Place the surfaces
        world.add(std::make_shared<sphere>(point3(0, -R, 0), R, mat_floor));        // Floor
        world.add(std::make_shared<sphere>(point3(0, R + 5.0, 0), R, mat_ceiling)); // Ceiling
        world.add(std::make_shared<sphere>(point3(0, 0, -R - 5.0), R, mat_back));   // Back wall
        world.add(std::make_shared<sphere>(point3(-R - 2.5, 0, 0), R, mat_left));   // Left wall
        world.add(std::make_shared<sphere>(point3(R + 2.5, 0, 0), R, mat_right));   // Right wall

        // Objects inside the room
        auto mat_glass = std::make_shared<dielectric>(1.5);
        auto mat_metal = std::make_shared<metal>(color(0.8, 0.85, 0.88), 0.0);

        world.add(std::make_shared<sphere>(point3(-1.0, 1.0, -2.5), 1.0, mat_glass));
        world.add(std::make_shared<sphere>(point3(1.0, 1.0, -1.5), 1.0, mat_metal));

        // Camera setup for an enclosed space
        cam.aspect_ratio = 1.0;
        cam.image_width = 600;
        cam.samples_per_pixel = 200; // Needs higher samples for enclosed bounces
        cam.max_depth = 50;
        cam.vfov = 60;
        cam.lookfrom = point3(0, 2.5, 6);
        cam.lookat = point3(0, 1.5, -2);
        cam.vup = vec3(0, 1, 0);
        cam.defocus_angle = 0.0;
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
            scene.name = "wide_angle_of_view";
            wide_angle_of_view(scene.world, scene.cam);
            break;

        case 2:
            scene.name = "hallow_glass_sphere";
            hallow_glass_sphere(scene.world, scene.cam);
            break;

        case 3:
            scene.name = "spheres_with_depth_of_field";
            spheres_with_depth_of_field(scene.world, scene.cam);
            break;

        case 4:
            scene.name = "final_scene";
            final_scene(scene.world, scene.cam, true);
            break;

        case 5:
            scene.name = "macro_marbles";
            macro_marbles(scene.world, scene.cam);
            break;

        case 6:
            scene.name = "sphere_room";
            sphere_room(scene.world, scene.cam);
            break;

        default:
            throw std::runtime_error("Invalid scene id: " + std::to_string(scene_id));
    }

    return scene;
}
