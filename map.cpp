#include "map.h"

Map::Map() {
    // Load & setup sprite
    View.t.loadFromFile("assets/background.png");
    View.sp.setTexture(View.t);
}

void Map::draw(sf::RenderWindow &window) {
    window.draw(View.sp);
}

sf::Vector2f Map::calculateOffset(sf::Vector2f pivot){
    // Get background texture size
    sf::Vector2u size = View.t.getSize();

    // Width offset
    if (pivot.x > 320 && size.x - pivot.x > 320) {
        Offset.x = pivot.x - 320;
    }

    // Height offset
    if (pivot.y > 240 && size.y - pivot.y > 240) {
        Offset.y = pivot.y - 240;
    }
    return Offset;
}

void Map::update() {
    View.sp.setPosition(-Offset.x, -Offset.y);
}
