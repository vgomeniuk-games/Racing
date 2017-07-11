#include "ai.h"
#include "globals.h"

AI::AI(int competitors) {
    for(int i = 0; i < competitors; ++i) {
        cars.push_back(std::unique_ptr<Car>(new Car(
                Globals::Width / 2 + (i + 1) * 50,
                Globals::Height / 2 + (i + 1) * 50,
                colors[i % colors.size()]
        )));
    }
}

void AI::update() {
    for (const auto& car : cars) {
        // TODO Replace with ai algorithm
        car->move(Direction::Up);
        car->move(Direction::Right);

        // Call update function with (0, 0) offset
        car->update([](sf::Vector2f) -> sf::Vector2f { return sf::Vector2f(); });
    }
}

void AI::draw(sf::RenderWindow& window) {
    for (const auto& car : cars) {
        car->draw(window);
    }
}