#ifndef VIEW_H
#define VIEW_H

#include "./constant.h"
#include "./piece.h"
#include "./game.h"
#include <SFML/Graphics.hpp>
#include <string>

class Model;

class View {
    private:
    sf::RenderWindow *window;
    sf::Font font;
    Game *controler;
    Model *model;

    public:
    void setControler(Game *game, Model *m);
    sf::RenderWindow *createWindow();
    sf::RenderWindow *getWindow();
    void drawTile(int px, int py, enum Tile color);
    void drawPiece(Piece &piece);
    void drawText(int px, int py, std::string text);
    void drawBoard(int **board);
    void drawPause();
    void drawHighscore(const std::vector<Highscore> &hs, unsigned int place);
    void drawPlayerNameOnHighscore(int place, std::string name);
    void drawMenu(int currSelection, int musicChoice, int soundChoice);
};

#endif
