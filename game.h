#ifndef GAME_H
#define GAME_H
#include "./piece.h"

class View;
class Model;

class Game {
    private:
    View &view;
    Model *model;
    Piece *currPiece;
    Piece *nextPiece;
    int **board;

    public:
    Game(Model *m, View &v);
    static int GetRandom(int inf, int sup);
    void launch();
    void setupNextPiece();
    void computePieceOnBoard();
    bool canRotate();
    bool canMoveLeft();
    bool canMoveRight();
    bool canMoveDown();
};

#endif
