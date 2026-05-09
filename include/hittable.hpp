#ifndef HITTABLE_H
#define HITTABLE_H

#include <interval.hpp>
#include <vec3.hpp>
#include <memory>
#include <ray.hpp>

class material;

class hit_record {
    public:
        point3 p;
        vec3 normal;
        double t;
        std::shared_ptr<material> mat;
        bool face_front;

        void set_face_normal(const ray& r, const vec3& outward_normal) {
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
