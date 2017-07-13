#ifndef RACING_UTILS_H
#define RACING_UTILS_H

#include <math.h>
#include <SFML/System/Vector2.hpp>

namespace Utils {
    float length(sf::Vector2f v) {
        return sqrtf(pow(v.x, 2) + pow(v.y, 2));
    };
}

#endif //RACING_UTILS_H
