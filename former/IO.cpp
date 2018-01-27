#include "./IO.h"

static SDL_Window *window;
static SDL_Surface *surf;
static uint32_t chromas[NB_COLORS] = {0x00ff0000, 0x0000ff00, 0x000000ff,
                                      0x00ffff00, 0x00ff00ff, 0x0000ffff,
                                      0x00707070, 0x00000000, 0x00ffffff};

IO::IO() { initGraph(); }

void IO::clearScreen() {
    boxColor(surf, 0, 0, surf->w - 1, surf->h - 1, chromas[BLACK]);
}

void IO::drawRectangle(int posX, int posY, int height, int width,
                       enum color col) {
    boxColor(surf, posX, posY, height, width, chromas[col]);
}

int IO::initGraph() {
    uint32_t windowFlags = SDL_WINDOW_SHOWN;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Could not initializa SDL : " << SDL_GetError()
                  << std::endl;
        return 1;
    } else {
        atexit(SDL_Quit);

        window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH,
                                  WINDOW_HEIGHT, windowFlags);
        if (window == NULL) {
            std::cout << "Error while creating the window : " << SDL_GetError()
                      << std::endl;
            return 2;
        } else {
            surf = SDL_GetWindowSurface(window);
        }
    }
    return 0;
}

int IO::pollKey() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_KEYDOWN:
            return event.key.keysym.sym;
        case SDL_QUIT:
            exit(3);
        }
    }
}

int IO::getKey() {
    SDL_Event event;

    while (true) {
        SDL_WaitEvent(&event);
        if (event.type == SDL_KEYDOWN)
            break;
        if (event.type = SDL_QUIT)
            exit(3);
    }
    return event.key.keysym.sym;
}

bool IO::isKeyDown(int key) {
    uint8_t *keyTable;
    int numKeys;
    SDL_PumpEvents();
    keyTable = SDL_GetKeyboardState(&numKeys);
    return keyTable[key];
}

void IO::updateScreen() { SDL_Flip(surf); }