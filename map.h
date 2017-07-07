#ifndef RACING_MAP_H
#define RACING_MAP_H

#include <SFML/Graphics.hpp>

class Map {
public:
    Map();
    void draw(sf::RenderWindow& window);
    sf::Vector2f offset(sf::Vector2f pivot);
    void update();
private:
    struct { sf::Sprite sp; sf::Texture t;  } View;
    sf::Vector2f Offset;
};


#endif //RACING_MAP_H
