#ifndef RACING_INPUT_H
#define RACING_INPUT_H

#include <SFML/Window/Keyboard.hpp>
#include <functional>
#include <initializer_list>
#include <map>
#include <vector>

class Input {
public:
    static void bind(std::initializer_list<sf::Keyboard::Key> keys, std::function<void()> callback);
    static void unbind(std::initializer_list<sf::Keyboard::Key> keys);
    static void update();
protected:
    Input();  // Forbid instantiating

private:
    // Singleton Input object
    static Input handler;

    // Bindings collection
    std::map<std::vector<sf::Keyboard::Key>, std::function<void()>> bindings;
};


#endif //RACING_INPUT_H
