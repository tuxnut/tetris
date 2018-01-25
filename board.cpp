#include "./board.h"

void Board::initBoard() {
    for (unsigned i = 0; i < BOARD_HEIGHT; i++) {
        for (unsigned j = 0; j < BOARD_WIDTH; j++) {
            mBoard[i][j] = FREE;
        }
    }
}

int Board::getXPosInPixels(int posX) {
    return BOARD_POS_X + (TILE_SIZE * posX);
}

int Board::getYPosInPixels(int posY) {
    return BOARD_POS_Y + (TILE_SIZE * posY);
}

void Board::computeShape(int posX, int posY) {
    for (int x = posX, i = 0; x < posX + SIZE_PIECE_SHAPE; x++, i++) {
        for (int y = posY, j = 0; y < posY + SIZE_PIECE_SHAPE; y++, j++) {
            mBoard[x][y] = (currPiece->getBlockAt(x, y) != FREE)
                               ? FILLED
                               : currPiece->getBlockAt(x, y);
        }
    }
}

bool Board::isGameOver() {
    for (unsigned i = 0; i < BOARD_WIDTH; i++) {
        if (mBoard[0][i] == FILLED)
            return true;
    }
    return false;
}

void Board::deleteLine(int line) {
    for (unsigned i = line; i > 0; i--) {
        for (unsigned j = 0; j < BOARD_WIDTH; j++) {
            mBoard[i][j] = mBoard[i - 1][j];
        }
    }
}

void Board::deletePossibleLines() {
    for (unsigned i = 0; i < BOARD_HEIGHT; i++) {
        int j = 0;
        while (j < BOARD_WIDTH) {
            if (mBoard[i][j] != FILLED)
                break;
            j++;
        }

        if (j == BOARD_WIDTH)
            deleteLine(i);
    }
}

bool Board::isPositionFree(int posX, int posY) {
    return (mBoard[posX][posY] == FREE) ? true : false;
}

bool Board::isMovementPossible(int posX, int posY) {
    for (int x = posX, i = 0; x < posX + SIZE_PIECE_SHAPE; x++, i++) {
        for (int y = posY, j = 0; y < posY + SIZE_PIECE_SHAPE; y++, j++) {
            // chack if deplacement move the piece outside the board
            if (x > 0 || x > BOARD_HEIGHT - 1 || y > BOARD_WIDTH - 1)
                if (currPiece->getBlockAt(i, j) != FREE)
                    return false;
                    
            // check collision with other pieces
            if (y >= 0)
                if (currPiece->getBlockAt(i, j) != FREE && !isPositionFree(x, y))
                    return false;
            
        }
    }

    return true;
}