#ifndef UTILITY_H
#define UTILITY_H

#include <cmath>
#include <iostream>
#include <limits>
#include <random>
#include <thread>
#include <omp.h>

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double random_double() {
    static thread_local std::mt19937 generator([] {
        std::seed_seq seed {
            std::random_device{}(),
            std::random_device{}(),
            static_cast<unsigned int>(
                std::hash<std::thread::id>{}(std::this_thread::get_id())
            ),
            static_cast<unsigned int>(omp_get_thread_num())
        };

        return std::mt19937(seed);
    }());

    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    return distribution(generator);
}

inline double random_double(double min, double max) {
    return min + (max-min) * random_double();
}

#endif