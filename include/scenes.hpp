#ifndef SCENES_H
#define SCENES_H

#include <hittable_list.hpp>
#include <camera.hpp>
#include <string>

struct Scene {
    int id;
    std::string name;
    hittable_list world;
    camera cam;
};

Scene make_scene(int scene_id);

#endif