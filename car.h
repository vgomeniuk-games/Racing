#ifndef RACING_CAR_H
#define RACING_CAR_H

#include <vector>
#include <string>
#include <functional>
#include <SFML/Graphics.hpp>

enum Direction { Up, Down, Left, Right, None};
enum PositionType { Absolute, Relative };

class Car {
public:
    Car(float x, float y, sf::Color color);
    void move(Direction direction);
    sf::Vector2f getPosition(PositionType type=Absolute);

    static void draw(sf::RenderWindow& window);
    static void update(sf::Vector2f Offset);

protected:
    void updateView(sf::Vector2f Offset);
    void updateMovement();
    void checkCollision(Car* other);

private:
    // Cars holder
    static std::vector<Car*> cars;
    static struct InfoType {
        float size{ 22.0f };
        std::string asset{"assets/car.png"};
    } Info;
    struct { sf::Sprite sp; sf::Texture t; } Sprites;
    struct {
        sf::Vector2f Absolute;
        sf::Vector2f Relative;
    } Position;
    struct { float current{ 0.0f }; float max{ 6.0f }; } Speed;
    struct { float angle{ 0.0f }; } Rotation;
    struct {
        float acc{ 0.2f };
        float turn{ 0.08f };
        bool moving{ false };
    } Transform;
};


#endif //RACING_CAR_H
