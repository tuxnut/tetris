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
    int score;
    int nbLines;
    int level;

    public:
    Game(Model *m, View &v);
    static int GetRandom(int inf, int sup);
    void launch();
    void setupNextPiece();
    void storePieceOnBoard();
    void deleteLine();
    void increaseScore(int line);
    void increaseLevel();
    bool canRotate();
    bool canMoveLeft();
    bool canMoveRight();
    bool canMoveDown();
    bool isGameOver();
};

#endif
