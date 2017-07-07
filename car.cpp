#include <math.h>
#include "car.h"

Car::Car(float x, float y, sf::Color color) {
    // Load & setup sprite
    View.t.loadFromFile("assets/car.png");
    View.sp.setTexture(View.t);
    View.sp.setOrigin(22, 22);
    View.sp.setColor(color);
    View.sp.setPosition(320, 240);  // TODO

    Position.x = x;
    Position.y = y;
}

void Car::move(Direction direction) {
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
            // Decelerate over time
            Speed.current > 0 ? Speed.current -= Transform.acc : Speed.current += Transform.acc;
            break;
    }
}

void Car::draw(sf::RenderWindow &window) {
    window.draw(View.sp);
}

void Car::update() {
    // Change position and rotation of the View
    Position.x += sin(Rotation.angle) * Speed.current;
    Position.y -= cos(Rotation.angle) * Speed.current;
    View.sp.setPosition(Position.x, Position.y);
    View.sp.setRotation(Rotation.angle * 180 / static_cast<float>(M_PI));
}
