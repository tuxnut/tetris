#include "./piece.h"
#include "./constant.h"
#include <stdlib.h>

Point Piece::getPosition() {
    return position;
}

void Piece::setPosition(Point p) {
    position = p;
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

int Piece::getBlockAt(int posX, int posY) {
    return shape[kind][variation][posX][posY];
}
