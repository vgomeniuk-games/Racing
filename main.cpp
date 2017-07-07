#include <math.h>
#include <functional>
#include <vector>
#include <SFML/Graphics.hpp>
#include "input.h"
#include "car.h"

int main() {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(640, 480), "Racing");
    window.setFramerateLimit(60);

    // Load sprites
    sf::Sprite background;
    sf::Texture t_back;
    t_back.loadFromFile("assets/background.png");
    background.setTexture(t_back);

    // TODO Map-related variables
    int background_w = background.getTextureRect().width;
    int background_h = background.getTextureRect().height;

    // TODO Car-related variables
    float x = 300, y=300;

    // Screen offset
    struct { int x{ 0 }; int y{ 0 }; } offset;

    Car car(320, 240, sf::Color::Green);

    // Main loop
    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent((e))) {
            if (e.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
        }
        // Handle keyboard input loop
        Input::handle({ sf::Keyboard::Up }, [&car](){car.move(Direction::Up);});
        Input::handle({ sf::Keyboard::Down }, [&car](){car.move(Direction::Down);});
        Input::handle({ sf::Keyboard::Up, sf::Keyboard::Down }, [&car](){car.move(Direction::None);});
        Input::handle({ sf::Keyboard::Left }, [&car](){car.move(Direction::Left);});
        Input::handle({ sf::Keyboard::Right },[&car](){car.move(Direction::Right);});

//        // Update car's position and rotation as well as background offset to display map correctly
//        x += sin(angle) * speed;
//        y -= cos(angle) * speed;
//        x > 320 && background_w - x > 320 ? (offset.x = x - 320) : 0;
//        y > 240 && background_h - y > 240 ? (offset.y = y - 240) : 0;
//        background.setPosition(-offset.x, -offset.y);

        // Update loop
        car.update();

        // Draw loop
        window.clear(sf::Color::White);
        window.draw(background);
        car.draw(window);
        window.display();
    }
    return 0;
}