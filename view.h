#include "./constant.h"
#include <SDL2/SDL.h>

class Game;

class View {
    private:
    SDL_Window *window;
    SDL_Surface *screen;
    Game *controler;

    public:
    void setControler(Game *game);

};