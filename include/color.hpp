#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include <cstdint>
#include <cmath>
#include <vec3.hpp>
#include <interval.hpp>

using color = vec3;

class byte3 {
public:
    uint8_t e[3];

    byte3() : e{0,0,0} {}

    byte3(uint8_t e0, uint8_t e1, uint8_t e2)
        : e{e0, e1, e2} {}

    uint8_t x() const { return e[0]; }
    uint8_t y() const { return e[1]; }
    uint8_t z() const { return e[2]; }

    friend std::ostream& operator<<(std::ostream& os, const byte3& b3);
};

inline std::ostream& operator<<(std::ostream& os, const byte3& b3) {
    os << static_cast<int>(b3.x()) << ' '
       << static_cast<int>(b3.y()) << ' '
       << static_cast<int>(b3.z());

    return os;
}

inline double linear_to_gamma(double linear_component) {
    return linear_component > 0.0
        ? std::sqrt(linear_component)
        : 0.0;
}

inline byte3 pixel_byte3(const color& pixel_color) {
    auto r = linear_to_gamma(pixel_color.x());
    auto g = linear_to_gamma(pixel_color.y());
    auto b = linear_to_gamma(pixel_color.z());

    static const interval intensity(0.000, 0.999);
    uint8_t rbyte = static_cast<uint8_t>(255.999 * intensity.clamp(r));
    uint8_t gbyte = static_cast<uint8_t>(255.999 * intensity.clamp(g));
    uint8_t bbyte = static_cast<uint8_t>(255.999 * intensity.clamp(b));

    return byte3(rbyte, gbyte, bbyte);
}

inline void write_color(std::ostream& out, const byte3& pixel_byte3) {
    out << pixel_byte3 << '\n';
}

#endif