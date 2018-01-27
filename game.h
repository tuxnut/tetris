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

    public:
    Game(Model *m, View &v);
    static int GetRandom(int inf, int sup);
    void launch();
    void setupNextPiece();
};

#endif
