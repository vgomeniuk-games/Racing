#ifndef RACING_INPUT_H
#define RACING_INPUT_H

#include <SFML/Window/Keyboard.hpp>
#include <functional>
#include <initializer_list>

class Input {
public:
    static void handle(std::initializer_list<sf::Keyboard::Key> keys, std::function<void()> callback);
};


#endif //RACING_INPUT_H
