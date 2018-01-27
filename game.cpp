#include "./game.h"
#include "./model.h"
#include "./view.h"

Game::Game(Model *m, View &v) : view(v) {
    model = m;
    view.setControler(this, m);
    srand((unsigned)time(NULL));
    currPiece = new Piece();
    nextPiece = new Piece();
    nextPiece->setX(NEXTPIECE_X);
    nextPiece->setY(NEXTPIECE_Y);
}

int Game::GetRandom(int inf, int sup) { return rand() % (sup - inf + 1) + inf; }

void Game::launch() {
    model->loadTiles();

    setupNextPiece();
    sf::RenderWindow *window = view.createWindow();

    while (window->isOpen()) {

        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();

            if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::Return) {
                    currPiece->rotate();
                }
                else if (event.key.code == sf::Keyboard::Left) {
                    currPiece->moveLeft();
                }
                else if (event.key.code == sf::Keyboard::Right) {
                    currPiece->moveRight();
                }

        }
        window->clear(sf::Color::White);

        // drawTile(10, 10, ORANGE);
        view.drawPiece(*currPiece);
        window->display();
    }
}

void Game::setupNextPiece() {
    // change nextPiece to currPiece
    currPiece->copy(*nextPiece);

    // get a new nextPiece
    nextPiece = new Piece();
}