#ifndef RACING_AI_H
#define RACING_AI_H

#include <vector>
#include <memory>
#include <SFML/Graphics/Color.hpp>
#include "car.h"

// simple racing AIController
class AIController {
public:
    AIController(int competitors);
    // Setup competitors
    std::vector<sf::Color> colors = {
            sf::Color::Red, sf::Color::Magenta, sf::Color::Cyan, sf::Color::Green,
            sf::Color::Black, sf::Color::White, sf::Color::Yellow, sf::Color::Blue
    };
    std::vector<std::unique_ptr<Car>> cars;

};


#endif //RACING_AI_H
