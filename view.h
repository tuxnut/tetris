#ifndef VIEW_H
#define VIEW_H

#include "./constant.h"
#include "./piece.h"
// #include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Game;
class Model;

class View {
    private:
    // SDL_Window *window;
    // SDL_Surface *screen;
    sf::RenderWindow *window;
    Game *controler;
    Model *model;

    public:
    void setControler(Game *game, Model *m);
    sf::RenderWindow *createWindow();
    void drawTile(int px, int py, enum Tile color);
    void drawPiece(Piece &piece);
    void drawBoard(int **board);
};

#endif
