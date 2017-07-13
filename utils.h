#ifndef RACING_UTILS_H
#define RACING_UTILS_H

#include <math.h>
#include <SFML/System/Vector2.hpp>

namespace Utils {
    static float length(sf::Vector2f v) {
        return sqrtf(powf(v.x, 2) + powf(v.y, 2));
    };
}

#endif //RACING_UTILS_H
