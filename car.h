#ifndef RACING_CAR_H
#define RACING_CAR_H

#include <functional>
#include <SFML/Graphics.hpp>

enum Direction { Up, Down, Left, Right, None};

class Car {
public:
    Car(float x, float y, sf::Color color);
    void move(Direction direction);
    void draw(sf::RenderWindow& window);
    void update(std::function<sf::Vector2f(sf::Vector2f)> calculateOffset);
private:
    struct { sf::Sprite sp; sf::Texture t; } View;
    struct {
        sf::Vector2f Absolute;
        sf::Vector2f Relative;
    } Position;
    struct { float current{ 0.0f }; float max{ 12.0f }; } Speed;
    struct { float angle{ 0.0f }; } Rotation;
    struct {
        float acc{ 0.2f };
        float turn{ 0.08f };
        bool moving{ false };
    } Transform;
};


#endif //RACING_CAR_H
