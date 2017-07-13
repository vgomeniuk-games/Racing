#include <math.h>
#include "car.h"

// Initialize static values
std::vector<Car*> Car::cars;
Car::InfoType Car::Info;

Car::Car(float x, float y, sf::Color color) {
    // Set start position
    Position.Absolute.x = x;
    Position.Absolute.y = y;

    // Load & setup sprite
    View.t.loadFromFile(Car::Info.asset);
    View.sp.setTexture(View.t);
    View.sp.setOrigin(Car::Info.size, Car::Info.size);
    View.sp.setColor(color);
    View.sp.setPosition(Position.Absolute.x, Position.Absolute.y);

    // Register instance
    Car::cars.push_back(this);
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

sf::Vector2f Car::getPosition(PositionType type) {
    return (type == Absolute ? Position.Absolute : Position.Relative);
}

void Car::update(sf::Vector2f Offset) {
    Position.Absolute.x += sin(Rotation.angle) * Speed.current;
    Position.Absolute.y -= cos(Rotation.angle) * Speed.current;
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

void Car::checkCollision() {
    for (int a = 0; a < cars.size(); ++a) {
        for (int b = a + 1; b < cars.size(); ++b) {

            sf::Vector2f posA = cars[a]->Position.Absolute;
            sf::Vector2f posB = cars[b]->Position.Absolute;
            sf::Vector2f dpos = posA - posB;

            // If 2 cars collide
            // Note: Compare pow(vector.length) and don't calculate sqrt()
            if(pow(dpos.x, 2) + pow(dpos.y, 2) < 2 * pow(Car::Info.size, 2)) {
                cars[a]->Position.Absolute += dpos / 5.0f;
                cars[b]->Position.Absolute -= dpos / 5.0f;
            }

        }
    }
}
