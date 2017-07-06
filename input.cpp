#include "input.h"

void Input::handle(std::initializer_list<sf::Keyboard::Key> keys, std::function<void()> callback) {
    for (auto& key : keys) {
        if(!sf::Keyboard::isKeyPressed(key)) {
            return;
        }
    }
    callback();
}