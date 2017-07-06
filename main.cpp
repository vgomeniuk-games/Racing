#include <SFML/Graphics.hpp>

int main() {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(640, 480), "Racing");
    window.setFramerateLimit(60);

    // Load sprites
    sf::Sprite background, car;
    sf::Texture t_back, t_car;
    t_back.loadFromFile("assets/background.png");
    t_car.loadFromFile("assets/car.png");
    background.setTexture(t_back);
    car.setTexture(t_car);

    // Main loop
    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent((e))) {
            if (e.type == sf::Event::Closed) {
                window.close();
            }
        }
        // Draw background
        window.clear(sf::Color::White);
        window.draw(background);

        // Draw a car
        car.setPosition(300, 300);
        car.setColor(sf::Color::Green);
        window.draw(car);

        window.display();
    }
    return 0;
}