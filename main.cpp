#include <SFML/Graphics.hpp>
#include "./constant.h"
#include <iostream>

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


///******* Mes test *********///

// class A {
//     public:
//     A() {};
//     A(A &example) { caca = example.caca; };
//     void copy(A &example) { caca = example.caca; };
//     int caca;
// };

// int main(int argc, char **argv) {
//     A *alpha = new A();
//     alpha->caca = 5;

//     A *beta = new A();
//     beta->copy(*alpha);

//     free(alpha);

//     std::cout << beta->caca << std::endl;

//     return 0;
// }
