#include <math.h>
#include <SFML/Graphics.hpp>
#include "input.h"

int main() {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(640, 480), "Racing");
    window.setFramerateLimit(60);

    // Load sprites
    sf::Sprite background, car;
    sf::Texture t_back, t_car;
    t_back.loadFromFile("assets/background.png");
    t_car.loadFromFile("assets/car.png");
    background.setTexture(t_back);
    car.setTexture(t_car);

    // Car setup (pivot point and color)
    car.setOrigin(22, 22);
    car.setColor(sf::Color::Green);
    car.setPosition(320, 240);

    // TODO Car-related variables
    float x = 300, y=300;
    float speed = 0, angle = 0;
    float maxSpeed = 12.0;
    float accelaration = 0.2, decelleration = 0.3;
    float turnSpeed = 0.08;

    // Screen offset
    struct { int x{ 0 }; int y{ 0 }; } offset;

    // Main loop
    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent((e))) {
            if (e.type == sf::Event::Closed) {
                window.close();
            }
        }
        // Handle keyboard input
        Input::handle({ sf::Keyboard::Up }, [&](){
            if (speed > maxSpeed) return;  // TODO limit car's speed
            speed < 0 ? speed += decelleration : speed += accelaration;
        });
        Input::handle({ sf::Keyboard::Down }, [&](){
            if (speed < -maxSpeed) return;  // TODO limit car's speed
            speed > 0 ? speed -= decelleration : speed -= accelaration;
        });
        Input::handle({ sf::Keyboard::Up, sf::Keyboard::Down }, [&](){
            // TODO Don't move if both Up & Down pressed
            speed - decelleration ? speed -= decelleration : (speed + decelleration < 0 ? speed += decelleration : 0);
        });
        Input::handle({ sf::Keyboard::Left }, [&](){ if(speed != 0) { angle -= turnSpeed * speed / maxSpeed; } });
        Input::handle({ sf::Keyboard::Right }, [&](){ if(speed != 0) { angle += turnSpeed * speed / maxSpeed; } });

        // Update car's position and rotation as well as background offset to display map correctly
        x += sin(angle) * speed;
        y -= cos(angle) * speed;
        x > 320 ? (offset.x = x - 320) : 0;
        y > 240 ? (offset.y = y - 240) : 0;
        background.setPosition(-offset.x, -offset.y);
        car.setPosition(x - offset.x, y - offset.y);
        car.setRotation(angle * 180 / static_cast<float>(M_PI));

        // Draw
        window.clear(sf::Color::White);
        window.draw(background);
        window.draw(car);
        window.display();
    }
    return 0;
}