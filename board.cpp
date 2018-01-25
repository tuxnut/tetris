#include "./board.h"

void Board::initBoard() {
    for(unsigned i = 0; i < BOARD_HEIGHT; i++) {
        for(unsigned j = 0; j < BOARD_WIDTH; j++) {
            mBoard[i][j] = FREE;
        }
    }
}

void Board::computeShape(int posX, int posY) {
    for(unsigned x = posX, i = 0; x < posX + SIZE_PIECE_SHAPE; x++, i++) {
        for(unsigned y = posY, j = 0; y < posY + SIZE_PIECE_SHAPE; y++, j++) {
            mBoard[x][y] = (currPiece->getBlockAt(x, y) != FREE) ? FILLED : currPiece->getBlockAt(x, y);
        }        
    }
}

bool Board::isGameOver() {
    for(unsigned i = 0; i < BOARD_WIDTH; i++) {
        if (mBoard[0][i] == FILLED) return true;
    }
    return false;
}
void Board::
void Board::
void Board::