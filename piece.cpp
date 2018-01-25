#include "./piece.h"

Piece::Piece(int k) {
    kind = k;
    variation = 0;
    position.x = INIT_NEXT_PIECE_X;
    position.y = INIT_NEXT_PIECE_Y;
}

Piece::Piece(Piece &piece) {
    kind = piece.kind;
    variation = piece.variation;
    position.x = piece.position.x;
    position.y = piece.position.y;
}

void Piece::copy(Piece &piece) {
    kind = piece.kind;
    variation = piece.variation;
    position.x = piece.position.x;
    position.y = piece.position.y;
}

Point Piece::getPosition() {
    return position;
}

void Piece::setPosition(Point p) {
    position = p;
}

void Piece::setPosition(int px, int py) {
    position.x = px;
    position.y = py;
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
