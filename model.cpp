#include "./model.h"

void Model::loadTiles() {
    tiles.loadFromFile("./res/tiles.png");
}

sf::Texture Model::getTiles() {
    return tiles;
}

sf::Sprite Model::getTileSprite(enum Tile color) {
    sf::Sprite sprite(tiles);

    sprite.setTextureRect(sf::IntRect(color * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE));
    return sprite;
}