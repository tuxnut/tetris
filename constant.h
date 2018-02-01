#ifndef CONSTANT_H
#define CONSTANT_H

#include <iostream>

#define WINDOW_HEIGHT 400
#define WINDOW_WIDTH 344
#define TILE_SIZE 18
#define NB_PIECES 7
#define NB_VARIATIONS 4
#define SIZE_PIECE_SHAPE 4
#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20
#define NEXTPIECE_X 12
#define NEXTPIECE_Y 15
#define BOARD_X 20
#define BOARD_Y 20
#define PIECE_OFFSET_X -2
#define PIECE_OFFSET_Y -1
#define BOARD_FREE 255
#define WAIT_TIME 700
#define MAX_LEVEL 10
#define TEXT_SCORE_X 263
#define TEXT_SCORE_Y 30
#define TEXT_LEVEL_X 264
#define TEXT_LEVEL_Y 100
#define TEXT_LINE_X 265
#define TEXT_LINE_Y 170
#define TEXT_NEXT_X 266
#define TEXT_NEXT_Y 270
#define TEXT_PAUSE_X 120
#define TEXT_PAUSE_Y 180
#define NB_SOUND 7

enum Tile { D_BLUE, PURPLE, RED, GREEN, YELLOW, L_BLUE, ORANGE, BLACK };

enum Shape { O_SHAPE, I_SHAPE, S_SHAPE, Z_SHAPE, J_SHAPE, L_SHAPE, T_SHAPE };

enum Sound {
    DELETE_LINE,
    MOVE,
    ROTATE,
    TETRIS,
    GATE_CLOSE,
    GAMEOVER,
    PIECE_FALLEN,
    LEVELUP
};

enum Music { MUSIC_A, MUSIC_B, SCORE };

inline static int TileToInt(enum Tile color) {
    switch(color) {
    D_BLUE:
        return 0;
    PURPLE:
        return 1;
    RED:
        return 2;
    GREEN:
        return 3;
    YELLOW:
        return 4;
    L_BLUE:
        return 5;
    ORANGE:
        return 6;
    }
}

inline static enum Tile IntToTile(int color) {
    switch(color) {
    D_BLUE:
        return D_BLUE;
    PURPLE:
        return PURPLE;
    RED:
        return RED;
    GREEN:
        return GREEN;
    YELLOW:
        return YELLOW;
    L_BLUE:
        return L_BLUE;
    ORANGE:
        return ORANGE;
    }
}

const int shape[NB_PIECES][NB_VARIATIONS][SIZE_PIECE_SHAPE][SIZE_PIECE_SHAPE] =
    {{// O_SHAPE
      {{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}},
      {{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}},
      {{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}},
      {{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}}},
     {// I_SHAPE
      {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},
      {{0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}},
      {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},
      {{0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}}},
     {// S_SHAPE
      {{0, 0, 0, 0}, {0, 0, 1, 1}, {0, 1, 1, 0}, {0, 0, 0, 0}},
      {{0, 0, 1, 0}, {0, 0, 1, 1}, {0, 0, 0, 1}, {0, 0, 0, 0}},
      {{0, 0, 0, 0}, {0, 0, 1, 1}, {0, 1, 1, 0}, {0, 0, 0, 0}},
      {{0, 0, 1, 0}, {0, 0, 1, 1}, {0, 0, 0, 1}, {0, 0, 0, 0}}},
     {// Z_SHAPE
      {{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 1}, {0, 0, 0, 0}},
      {{0, 0, 1, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}},
      {{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 1}, {0, 0, 0, 0}},
      {{0, 0, 1, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}}},
     {// J_SHAPE
      {{0, 0, 0, 0}, {0, 1, 1, 1}, {0, 0, 0, 1}, {0, 0, 0, 0}},
      {{0, 0, 1, 1}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}},
      {{0, 1, 0, 0}, {0, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},
      {{0, 0, 1, 0}, {0, 0, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}}},
     {// L_SHAPE
      {{0, 0, 0, 0}, {0, 1, 1, 1}, {0, 1, 0, 0}, {0, 0, 0, 0}},
      {{0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 1}, {0, 0, 0, 0}},
      {{0, 0, 0, 1}, {0, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},
      {{0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}}},
     {// T_SHAPE
      {{0, 0, 0, 0}, {0, 1, 1, 1}, {0, 0, 1, 0}, {0, 0, 0, 0}},
      {{0, 0, 1, 0}, {0, 0, 1, 1}, {0, 0, 1, 0}, {0, 0, 0, 0}},
      {{0, 0, 1, 0}, {0, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},
      {{0, 0, 1, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}}}};

static void DisplayShape(int k, int v) {
    for(unsigned i = 0; i < SIZE_PIECE_SHAPE; i++) {
        for(unsigned j = 0; j < SIZE_PIECE_SHAPE; j++) {
            std::cout << shape[k][v][i][j] << "\t";
        }
        std::cout << std::endl;
    }
}
#endif
