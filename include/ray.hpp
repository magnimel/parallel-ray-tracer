#ifndef RAY_H
#define RAY_H

class ray {
    private:
        point3 orig;
        vec3 dir;

    public:
        ray() : orig(point3()), dir(vec3()) {}

        ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {};

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