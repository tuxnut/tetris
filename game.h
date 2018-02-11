#ifndef GAME_H
#define GAME_H
#include "./piece.h"
#include <string.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class View;
class Model;

class Game {
  private:
    enum GameState state;
    View &view;
    Model *model;
    Piece *currPiece;
    Piece *nextPiece;
    sf::Music music;
    sf::Sound sound;
    sf::Clock timer;
    std::vector<sf::SoundBuffer> buffers;
    int **board;
    int score;
    int nbLines;
    int level;
    int nbPiece;
    int waitTimer;
    int menuSelection;

  public:
    Game(Model *m, View &v);
    ~Game();
    static int GetRandom(int inf, int sup);
    static float GetRandom(float inf, float sup);
    int getScore();
    int getLines();
    int getLevel();
    int getNbPiece();
    void launch();
    void startGame(sf::RenderWindow *window);
    void pauseGame(sf::RenderWindow *window);
    void displayHighscore(sf::RenderWindow *window);
    void displayMenu(sf::RenderWindow *window);
    void resetBoard();
    void setupNextPiece();
    void storePieceOnBoard();
    void deleteLine();
    void increaseScore(int line);
    void increaseLevel();
    void loadSound();
    void playSound(enum Sound sound);
    bool canRotate();
    bool canMoveLeft();
    bool canMoveRight();
    bool canMoveDown();
    bool isGameOver();
    int isHighscore(std::vector<Highscore> &hs);
};

#endif
