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

void Game::drawPiece(Piece &piece) {
    color mColor;

    int ppx = board->getXPosInPixels(piece.getPosition().x);
    int ppy = board->getYPosInPixels(piece.getPosition().y);

    // draw the block that are filled from the shape of the currPiece
    for(unsigned i = 0; i < SIZE_PIECE_SHAPE; i++) {
        for(unsigned j = 0; j < SIZE_PIECE_SHAPE; j++) {
            switch(piece.getBlockAt(i, j)) {
            case 1:
                mColor = GREEN;
                break;
            case 2:
                mColor = BLUE;
                break;
            }

            if(piece.getBlockAt(i, j) != FREE) {
                // io->drawRectangle(ppx + i * TILE_SIZE, ppy + j * TILE_SIZE, );
            }
        }
    }
}

void Game::drawBoard() {
    const int boardWidthInPixels = BOARD_WIDTH * TILE_SIZE;
    const int boardHeightInPixels = BOARD_HEIGHT * TILE_SIZE;

    io->drawRectangle(BOARD_POS_X, BOARD_POS_Y, boardHeightInPixels,
                      boardWidthInPixels,
                      /* color */);

    for(unsigned i = 0; i < BOARD_HEIGHT; i++) {
        for(unsigned j = 0; j < BOARD_WIDTH; j++) {
            if(!board->isPositionFree(i, j)) {
                io->drawRectangle(BOARD_POS_X + i * TILE_SIZE, BOARD_POS_Y + j * TILE_SIZE, TILE_SIZE, TILE_SIZE, /* color */);
            }
        }
    }
}

void Game::drawScene() {
    drawBoard();
    drawPiece(*currPiece);
    drawPiece(*nextPiece);
}
