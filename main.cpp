#include <functional>
#include <SFML/Graphics.hpp>
#include "input.h"
#include "car.h"
#include "map.h"
#include "ai.h"
#include "globals.h"

int main() {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(Globals::Width, Globals::Height), "Racing");
    window.setFramerateLimit(60);

    // Setup actors
    Map map;
    Car car(Globals::Width / 2, Globals::Height / 2, sf::Color::Green);
    AI competitors(1);

    // Bind input with proper callbacks
    Input::bind({ sf::Keyboard::Up }, [&car](){car.move(Direction::Up);});
    Input::bind({ sf::Keyboard::Down }, [&car](){car.move(Direction::Down);});
    Input::bind({ sf::Keyboard::Up, sf::Keyboard::Down }, [&car](){car.move(Direction::None);});
    Input::bind({ sf::Keyboard::Left }, [&car](){car.move(Direction::Left);});
    Input::bind({ sf::Keyboard::Right },[&car](){car.move(Direction::Right);});

    // Main loop
    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent((e))) {
            if (e.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
        }
        // Update
        Input::update();
        map.calculateOffset(car.getPosition());
        map.update();
        car.update(map.getOffset());
        competitors.update(map.getOffset());
        Car::checkCollision();

        // Draw
        window.clear(sf::Color::White);
        map.draw(window);
        car.draw(window);
        competitors.draw(window);
        window.display();
    }
    return 0;
}