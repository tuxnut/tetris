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
    // The pieces hold their position in the board
    // Convert from place in board to real pixel ! 

    int px = piece.getX();
    int py = piece.getY();
    int kind = piece.getKind();
    int variation = piece.getVariation();
    enum Tile color = piece.getColor();


    for(unsigned i = 0; i < SIZE_PIECE_SHAPE; i++) {
        for(unsigned j = 0; j < SIZE_PIECE_SHAPE; j++) {
            if(shape[kind][variation][j][i] != 0) {
                drawTile(BOARD_X + (px + i) * TILE_SIZE, BOARD_Y + (py + j) * TILE_SIZE, color);
            }
        }
    }
}

void View::drawBoard(int **board) {
    for(unsigned i = 0; i < BOARD_WIDTH + 2; i++) {
        drawTile((BOARD_X - TILE_SIZE) + i * TILE_SIZE, BOARD_Y - TILE_SIZE, BLACK);
        drawTile((BOARD_X - TILE_SIZE) + i * TILE_SIZE, BOARD_Y + BOARD_HEIGHT * TILE_SIZE, BLACK);
    }
    for(unsigned i = 0; i < BOARD_HEIGHT; i++) {
        drawTile((BOARD_X - TILE_SIZE), BOARD_Y + i * TILE_SIZE, BLACK);
        drawTile((BOARD_X + BOARD_WIDTH * TILE_SIZE), BOARD_Y + i * TILE_SIZE, BLACK);
    }

    for(unsigned i = 0; i < BOARD_WIDTH; i++)
        for(unsigned j = 0; j < BOARD_HEIGHT; j++)
            if (board[i][j] != BOARD_FREE)
                drawTile(BOARD_X + i* TILE_SIZE, BOARD_Y + j * TILE_SIZE, IntToTile(board[i][j]));
}
