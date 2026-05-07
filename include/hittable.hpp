#ifndef HITTABLE_H
#define HITTABLE_H

#include "vec3.hpp"
#include "ray.hpp"

class hit_record {
    public:
        point3 p;
        vec3 normal;
        double t;
        bool face_front;

        void set_face_normal(const ray& r, const vec3& outward_normal) {
            // outward_normal is unit vector
            face_front = dot(r.direction(), outward_normal) < 0.0;
            normal = face_front ? outward_normal : -outward_normal;
        }
};

class hittable {
    public:
        virtual ~hittable() = default;
        virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;
};

#endif
