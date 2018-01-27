#ifndef MODEL_H
#define MODEL_H

#include <SFML/Graphics.hpp>
#include "./constant.h"

class Model {
    sf::Texture tiles;

    public:    
    // Model();
    void loadTiles();
    sf::Texture getTiles();
    sf::Sprite getTileSprite(enum Tile color);
};

#endif
