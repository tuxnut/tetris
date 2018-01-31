#ifndef GAME_H
#define GAME_H
#include "./piece.h"
#include <SFML/Audio.hpp>

class View;
class Model;

class Game {
    private:
    View &view;
    Model *model;
    Piece *currPiece;
    Piece *nextPiece;
    sf::Music music;
    sf::Sound sound;
    std::vector<sf::SoundBuffer> buffers;
    int **board;
    int score;
    int nbLines;
    int level;
    int nbPiece;

    public:
    Game(Model *m, View &v);
    static int GetRandom(int inf, int sup);
    int getScore();
    int getLines();
    int getLevel();
    int getNbPiece();
    void launch();
    void pauseGame();
    void finishGame();
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
};

#endif
