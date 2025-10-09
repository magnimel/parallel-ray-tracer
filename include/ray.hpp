#ifndef RAY_H
#define RAY_H

#include "vec3.hpp"

class ray {
    private:
        point3 orig;
        vec3 dir;

    public:
        ray(point3& origin, vec3& direction) : orig(origin), dir(direction) {};

        point3 at(double t) const {
            return orig + t * dir;
        }

        const point3& origin() const {
            return orig;
        }

        const vec3& direction() const {
            return dir;
        }

        
};

double hit_sphere(const point3& center, double radius, const ray& r) {
    vec3 oc = center - r.origin();
    auto a = dot(r.direction(), r.direction());
    auto h = dot(r.direction(), oc);
    auto c = dot(oc, oc) - radius*radius;
    auto discriminant = h*h - a*c;

    if (discriminant < 0) return -1.0;
    return (h - std::sqrt(discriminant)) / a;
}

color ray_color(const ray& r) {
    auto t = hit_sphere(point3(0, 0, -1), 0.5, r);
    if (t > 0.0) {
        vec3 N = unit_vector(r.at(t) - point3(0, 0, -1));
        return 0.5 * color(N.x()+1, N.y()+1, N.z()+1);
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}


#endif