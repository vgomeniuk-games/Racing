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

void Car::update() {
    // Change position and rotation of the View
    Position.x += sin(Rotation.angle) * Speed.current;
    Position.y -= cos(Rotation.angle) * Speed.current;
    View.sp.setPosition(Position.x, Position.y);
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
