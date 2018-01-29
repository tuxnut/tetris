#include "./model.h"

void Model::loadTiles() {
    tiles.loadFromFile("./res/tiles.png");
}

void Model::loadMusic(sf::Music *music) {
    if (!music->openFromFile("./res/tetris.ogg"))
        std::cout << "Could not open music file" << std::endl;
}

sf::SoundBuffer Model::loadSound(enum Sound sound) {
    sf::SoundBuffer sb;
    switch (sound)
    {
    case PIECE_FALLEN:
        sb.loadFromFile("./res/fall.ogg");
        break;
    }

    return sb;
}

sf::Texture Model::getTiles() {
    return tiles;
}

sf::Sprite Model::getTileSprite(enum Tile color) {
    sf::Sprite sprite(tiles);

    sprite.setTextureRect(sf::IntRect(color * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE));
    return sprite;
}
