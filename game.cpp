#include "./game.h"

int Game::getRand(int inf, int sup) { return rand() % (sup - inf + 1) + inf; }

void Game::initGame() {
    // seed for RNG
    srand((unsigned)time(NULL));

    // first piece
    currPiece = new Piece(getRand(0, NB_PIECES - 1));
    currPiece->setPosition(INIT_PIECE_ON_BOARD_X + INIT_PIECE_PIVOT_X,
                           INIT_PIECE_ON_BOARD_Y + INIT_PIECE_PIVOT_Y);

    // next piece
    nextPiece = new Piece(getRand(0, NB_PIECES - 1));
}

void Game::createNewPiece() {
    currPiece->copy(*nextPiece);
    currPiece->setPosition(INIT_PIECE_ON_BOARD_X + INIT_PIECE_PIVOT_X,
                           INIT_PIECE_ON_BOARD_Y + INIT_PIECE_PIVOT_Y);

    // free(nextPiece);
    nextPiece = new Piece(getRand(0, NB_PIECES - 1));
}

void Game::drawPiece() {
    color mColor;

    int ppx = board->getXPosInPixels(currPiece->getPosition().x);
    int ppy = board->getYPosInPixels(currPiece->getPosition().y);

    // draw the block that are filled from the shape of the currPiece
    for (unsigned i = 0; i < SIZE_PIECE_SHAPE; i++) {
        for (unsigned j = 0; j < SIZE_PIECE_SHAPE; j++) {
            switch (currPiece->getBlockAt(i, j)) {
            case 1:
                mColor = GREEN;
                break;
            case 2:
                mColor = BLUE;
                break;
            }

            if(currPiece->getBlockAt(i, j) != FREE) {
                io->drawRectangle(ppx + i * TILE_SIZE, ppy + j * TILE_SIZE, );
            }
        }
    }
}
