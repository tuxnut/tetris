#include "./view.h"
#include "./model.h"

void View::setControler(Game *game, Model *m) {
    controler = game;
    model = m;
}

sf::RenderWindow *View::createWindow() {
    window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tetris");

    return window;
}

void View::drawTile(int px, int py, enum Tile color) {
    sf::Sprite sprite = model->getTileSprite(color);
    sprite.setPosition(px, py);
    window->draw(sprite);
    // window->display();
}

void View::drawPiece(Piece &piece) {
    int px = piece.getX();
    int py = piece.getY();
    int kind = piece.getKind();
    int variation = piece.getVariation();
    enum Tile color = piece.getColor();

    for(unsigned i = 0; i < SIZE_PIECE_SHAPE; i++) {
        for(unsigned j = 0; j < SIZE_PIECE_SHAPE; j++) {
            if(shape[kind][variation][i][j] != 0) {
                drawTile(px + i * TILE_SIZE, py + j* TILE_SIZE, color);
            }
        }
    }
}