#include <math.h>
#include <functional>
#include <vector>
#include <SFML/Graphics.hpp>
#include "input.h"
#include "car.h"
#include "map.h"

int main() {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(640, 480), "Racing");
    window.setFramerateLimit(60);

    // Setup actors
    Map map;
    Car car(320, 240, sf::Color::Green);

    // Main loop
    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent((e))) {
            if (e.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
        }
        // Handle keyboard input
        Input::handle({ sf::Keyboard::Up }, [&car](){car.move(Direction::Up);});
        Input::handle({ sf::Keyboard::Down }, [&car](){car.move(Direction::Down);});
        Input::handle({ sf::Keyboard::Up, sf::Keyboard::Down }, [&car](){car.move(Direction::None);});
        Input::handle({ sf::Keyboard::Left }, [&car](){car.move(Direction::Left);});
        Input::handle({ sf::Keyboard::Right },[&car](){car.move(Direction::Right);});

        // Update
        car.update([&map](sf::Vector2f position){return map.calculateOffset(position);});
        map.update();

        // Draw
        window.clear(sf::Color::White);
        map.draw(window);
        car.draw(window);
        window.display();
    }
    return 0;
}