#include "./IO.h"

static SDL_Surface *surf;
static uint32_t colors[NB_COLORS] = {
    0x00ff0000,
    0x0000ff00,
    0x000000ff,
    0x00ffff00,
    0x00ff00ff,
    0x0000ffff,
    0x00707070,
    0x00000000,
    0x00ffffff
}