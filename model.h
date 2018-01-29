#ifndef MODEL_H
#define MODEL_H

#include <SFML/Graphics.hpp>
#include "./constant.h"
#include <SFML/Audio.hpp>

class Model {
    sf::Texture tiles;

    public:    
    // Model();
    void loadTiles();
    void loadMusic(sf::Music *music);
    sf::SoundBuffer loadSound(enum Sound sound);
    sf::Texture getTiles();
    sf::Sprite getTileSprite(enum Tile color);
};

#endif
