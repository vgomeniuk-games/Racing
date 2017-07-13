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
    Sprites.t.loadFromFile(Car::Info.asset);
    Sprites.sp.setTexture(Sprites.t);
    Sprites.sp.setOrigin(Car::Info.size, Car::Info.size);
    Sprites.sp.setColor(color);
    Sprites.sp.setPosition(Position.Absolute.x, Position.Absolute.y);

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
    for (auto car : cars) {
        window.draw(car->Sprites.sp);
    }
}

sf::Vector2f Car::getPosition(PositionType type) {
    return (type == Absolute ? Position.Absolute : Position.Relative);
}

void Car::update(sf::Vector2f Offset) {
    for (int i = 0; i < cars.size(); ++i) {
        // Update position on screen and movement
        cars[i]->updateView(Offset);
        cars[i]->updateMovement();

        // Check if collides with other cars
        for(int j = i; j < cars.size(); ++j) {
            cars[i]->checkCollision(cars[j]);
        }
    }
}

void Car::updateView(sf::Vector2f Offset) {
    Position.Absolute.x += sin(Rotation.angle) * Speed.current;
    Position.Absolute.y -= cos(Rotation.angle) * Speed.current;
    Position.Relative.x = Position.Absolute.x - Offset.x;
    Position.Relative.y = Position.Absolute.y - Offset.y;

    // Update position and rotation
    Sprites.sp.setPosition(Position.Relative);
    Sprites.sp.setRotation(Rotation.angle * 180 / static_cast<float>(M_PI));
}

void Car::updateMovement() {
    // Decelerate over time if no movement registered
    if (!Transform.moving) {
        if (Speed.current > Transform.acc) { Speed.current -= Transform.acc; }
        else if (Speed.current < -Transform.acc) { Speed.current += Transform.acc; }
        else { Speed.current = 0; }
    }
    // Reset movement observer at the end of a frame update
    Transform.moving = false;
}

void Car::checkCollision(Car* other) {
    // Get distance to other car
    sf::Vector2f distance = this->Position.Absolute - other->Position.Absolute;

    // Check if collide
    // Note: Compare pow(vector.length) and don't calculate sqrt()
    if(pow(distance.x, 2) + pow(distance.y, 2) < 2 * pow(Car::Info.size, 2)) {
        // Slide a bit to different direction
        this->Position.Absolute += distance / 5.0f;
        other->Position.Absolute -= distance / 5.0f;
    }
}
