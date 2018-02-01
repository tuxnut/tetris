#ifndef MODEL_H
#define MODEL_H

#include "./constant.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <fstream>

class Model {
    sf::Texture tiles;

  public:
    // Model();
    void loadTiles();
    void loadMusic(sf::Music *music, enum Music m);
    sf::SoundBuffer loadSound(enum Sound sound);
    sf::Texture getTiles();
    sf::Sprite getTileSprite(enum Tile color);
    std::vector<Highscore> loadHighscores();
    bool writeHighscores(const std::vector<Highscore> &hs) const;
};

#endif
