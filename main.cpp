#include <functional>
#include <SFML/Graphics.hpp>
#include "input.h"
#include "car.h"
#include "map.h"
#include "ai.h"

int main() {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(640, 480), "Racing");
    window.setFramerateLimit(60);

    // Setup actors
    Map map;
    Car car(320, 240, sf::Color::Green);
    AI competitors(5);

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
        car.update([&map](sf::Vector2f position){return map.calculateOffset(position);});
        map.update();
        competitors.update();

        // Draw
        window.clear(sf::Color::White);
        map.draw(window);
        car.draw(window);
        competitors.draw(window);
        window.display();
    }
    return 0;
}