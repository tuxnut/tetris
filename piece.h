#ifndef PIECE_H
#define PIECE_H

#include "./constant.h"

class Piece {
    private:
    int px;
    int py;
    int kind;
    int variation;
    enum Tile color;

    public:
    Piece();
    Piece(int x, int y);

    void copy(Piece &piece);
    int getX();
    void setX(int x);
    int getY();
    void setY(int y);
    int getKind();
    void setKind(int k);
    int getVariation();
    void setVariation(int v);
    enum Tile getColor();
    void rotate();
    void moveLeft();
    void moveRight();
    void moveDown();
};

#endif