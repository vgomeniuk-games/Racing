#include "map.h"
#include "globals.h"

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
    float wo = Globals::Width / 2;
    if (pivot.x > wo && size.x - pivot.x > wo) {
        Offset.x = pivot.x - wo;
    }

    // Height offset
    float ho = Globals::Height / 2;
    if (pivot.y > wo && size.y - pivot.y > wo) {
        Offset.y = pivot.y - wo;
    }
    return Offset;
}

void Map::update() {
    View.sp.setPosition(-Offset.x, -Offset.y);
}
