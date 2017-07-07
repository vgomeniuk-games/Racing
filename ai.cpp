#include "ai.h"

AI::AI(int competitors) {
    for(int i = 0; i < competitors; ++i) {
        cars.push_back(std::unique_ptr<Car>(new Car(320 + i * 50, 240 + i * 50, colors[i % colors.size()])));
    }
}

void AI::update() {

}

void AI::draw(sf::RenderWindow& window) {
    for (const auto& car : cars) {
        car->draw(window);
    }
}