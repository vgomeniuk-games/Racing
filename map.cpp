#include "map.h"

Map::Map() {
    // Load & setup sprite
    View.t.loadFromFile("assets/background.png");
    View.sp.setTexture(View.t);
}

void Map::draw(sf::RenderWindow &window) {
    window.draw(View.sp);
}
