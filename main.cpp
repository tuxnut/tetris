#include <SFML/Graphics.hpp>
#include "./constant.h"

int main(int argc, char **argv) {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "My Window");

    sf::Texture tex;
    tex.loadFromFile("./res/tiles.png");

    sf::Sprite sprite(tex);

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }
    return 0;
}