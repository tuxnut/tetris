#include "./piece.h"
#include "./game.h"

#include <iostream>

Piece::Piece() {
    kind = Game::GetRandom(0, NB_PIECES - 1);
    variation = 0;
    color = IntToTile(kind);
}

Piece::Piece(int x, int y) {
    kind = Game::GetRandom(0, NB_PIECES - 1);
    variation = 0;
    color = IntToTile(kind);
    px = x;
    py = y;
}

void Piece::copy(Piece &piece) {
    std::cout << __LINE__ << std::endl;
    px = piece.getX();
    std::cout << __LINE__ << std::endl;
    py = piece.getY();
    kind = piece.getKind();
    variation = piece.getVariation();
    color = piece.getColor();
}

int Piece::getX() {
    return px;
}

void Piece::setX(int x) {
    px = x;
}

int Piece::getY() {
    return py;
}

void Piece::setY(int y) {
    py = y;
}

int Piece::getKind() {
    return kind;
}

void Piece::setKind(int k) {
    kind = k;
}

int Piece::getVariation() {
    return variation;
}

void Piece::setVariation(int v) {
    variation = v;
}

enum Tile Piece::getColor() {
    return color;
}

void Piece::rotate() {
    variation = (variation == NB_VARIATIONS - 1) ? 0 : variation + 1;
}

void Piece::moveLeft() {
    px--;
}

void Piece::moveRight() {
    px++;
}
void Piece::moveDown() {
    py++;
}
