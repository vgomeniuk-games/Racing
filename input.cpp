#include "input.h"

Input Input::handler;

Input::Input() {}

void Input::bind(std::initializer_list<sf::Keyboard::Key> keys, std::function<void()> callback) {
    // Create and register binding
    handler.bindings[keys] = callback;
}

void Input::unbind(std::initializer_list<sf::Keyboard::Key> keys) {
    // De-register binding - requires the exactly the same { keys } as when registered;
    handler.bindings.erase(keys);
}

void Input::update() {
    for(auto& binding : handler.bindings) {
        bool dispatch = true;
        for (auto& key : binding.first) {
            if (dispatch && !sf::Keyboard::isKeyPressed(key)) {
                dispatch = false;
            }
        }
        if (dispatch) {
            binding.second();
        }
    }
}