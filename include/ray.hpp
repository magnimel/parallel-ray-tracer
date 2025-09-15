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

#endif