#ifndef RACING_MAP_H
#define RACING_MAP_H

#include <SFML/Graphics.hpp>

class Map {
public:
    Map();
    void draw(sf::RenderWindow& window) const;
    sf::Vector2f calculateOffset(sf::Vector2f pivot);
    sf::Vector2f getOffset() const;
    void update();

private:
    struct {
        sf::Sprite sp;
        sf::Texture t;
        sf::Vector2f Offset;
    } View;
};


#endif //RACING_MAP_H
