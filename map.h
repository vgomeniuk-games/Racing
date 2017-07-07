#ifndef RACING_MAP_H
#define RACING_MAP_H

#include <SFML/Graphics.hpp>

class Map {
public:
    Map();
    void draw(sf::RenderWindow& window);
private:
    struct { sf::Sprite sp; sf::Texture t; } View;
    struct { int x{ 0 }; int y{ 0 }; } Offset;
};


#endif //RACING_MAP_H
