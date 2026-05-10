#ifndef RAY_H
#define RAY_H

#include <vec3.hpp>

class ray {
    private:
        point3 orig;
        vec3 dir;
        double tm;

    public:
        ray() : orig(point3()), dir(vec3()), tm(0.0) {}

        ray(const point3& origin, const vec3& direction, double time) : orig(origin), dir(direction), tm(time) {};

        ray(const point3& origin, const vec3& direction) : ray(origin, direction, 0.0) {};

        point3 at(double t) const {
            return orig + t * dir;
        }

        const point3& origin() const {
            return orig;
        }

        const vec3& direction() const {
            return dir;
        }

        double time() const {
            return tm;
        }

};


#endif