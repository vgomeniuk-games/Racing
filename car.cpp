#include <math.h>
#include "car.h"

Car::Car(float x, float y, sf::Color color) {
    // Set start position
    Position.Absolute.x = x;
    Position.Absolute.y = y;

    // Load & setup sprite
    View.t.loadFromFile("assets/car.png");
    View.sp.setTexture(View.t);
    View.sp.setOrigin(22, 22);
    View.sp.setColor(color);
    View.sp.setPosition(Position.Absolute.x, Position.Absolute.y);
}

void Car::move(Direction direction) {
    // If method is called - objet is probably moving
    Transform.moving = true;
    switch (direction) {
        case Up:
            if (Speed.current > Speed.max) { break; };
            Speed.current += Transform.acc;
            break;
        case Down:
            if (Speed.current < -Speed.max) { break; };
            Speed.current -= Transform.acc;
            break;
        case Right:
            if (Speed.current) {
                Rotation.angle += Transform.turn * Speed.current / Speed.max;
            };
            break;
        case Left:
            if (Speed.current) {
                Rotation.angle -= Transform.turn * Speed.current / Speed.max;
            };
            break;
        default:
            // Register bindings to None as signal to stop moving
            Transform.moving = false;
            break;
    }
}

void Car::draw(sf::RenderWindow &window) {
    window.draw(View.sp);
}

void Car::update(std::function<sf::Vector2f(sf::Vector2f)> calculateOffset) {
    // Calculate correct position
    Position.Absolute.x += sin(Rotation.angle) * Speed.current;
    Position.Absolute.y -= cos(Rotation.angle) * Speed.current;
    auto Offset = calculateOffset(Position.Absolute);
    Position.Relative.x = Position.Absolute.x - Offset.x;
    Position.Relative.y = Position.Absolute.y - Offset.y;

    // Update position and rotation
    View.sp.setPosition(Position.Relative);
    View.sp.setRotation(Rotation.angle * 180 / static_cast<float>(M_PI));

    // Decelerate over time if no movement registered
    if (!Transform.moving) {
        if (Speed.current > Transform.acc) { Speed.current -= Transform.acc; }
        else if (Speed.current < -Transform.acc) { Speed.current += Transform.acc; }
        else { Speed.current = 0; }
    }

    // Reset movement observer at the end of a frame update
    Transform.moving = false;
}
