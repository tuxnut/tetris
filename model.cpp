#include "./model.h"

void Model::loadTiles() { tiles.loadFromFile("./res/tiles.png"); }

void Model::loadMusic(sf::Music *music, enum Music m) {
    switch (m) {
    case MUSIC_A:
        if (!music->openFromFile("./res/music-A.ogg"))
            std::cout << "Could not open music file" << std::endl;
        break;
    case MUSIC_B:
        if (!music->openFromFile("./res/music-B.ogg"))
            std::cout << "Could not open music file" << std::endl;
        break;
    case SCORE:
        if (!music->openFromFile("./res/score.ogg"))
            std::cout << "Could not open music file" << std::endl;
        break;
    }
}

sf::SoundBuffer Model::loadSound(enum Sound sound) {
    sf::SoundBuffer sb;
    switch (sound) {
    case DELETE_LINE:
        sb.loadFromFile("./res/clearline.ogg");
        break;
    case MOVE:
        sb.loadFromFile("./res/pauline.ogg");
        break;
    case ROTATE:
        sb.loadFromFile("./res/move.ogg");
        break;
    case TETRIS:
        sb.loadFromFile("./res/tetris.ogg");
        break;
    case GATE_CLOSE:
        sb.loadFromFile("./res/gateclose.ogg");
        break;
    case GAMEOVER:
        sb.loadFromFile("./res/gameover.ogg");
        break;
    case LEVELUP:
        sb.loadFromFile("./res/levelup.ogg");
        break;
    case PIECE_FALLEN:
        sb.loadFromFile("./res/fall.ogg");
        break;
    }
    return sb;
}

sf::Texture Model::getTiles() { return tiles; }

sf::Sprite Model::getTileSprite(enum Tile color) {
    sf::Sprite sprite(tiles);

    sprite.setTextureRect(
        sf::IntRect(color * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE));
    return sprite;
}

std::vector<Highscore> Model::loadHighscores() {
    std::vector<Highscore> hs;
    std::ifstream ifs("./highscore.dat");

    ifs.seekg(0, ifs.end);
    int length = ifs.tellg();
    ifs.seekg(0, ifs.beg);

    int nbHighscores = length / sizeof(Highscore);

    for(int i = 0; i < nbHighscores; i++) {
        Highscore high;
        ifs.read((char *)&high, sizeof(Highscore));
        hs.push_back(high);
    }
    ifs.close();
    return hs;
}

bool Model::writeHighscores(const std::vector<Highscore> &hs) const {
    std::ofstream ofs("./highscore.dat", std::ios::binary);

    for(unsigned i = 0; i < hs.size(); i++) {
        ofs.write((char *)&hs[i], sizeof(Highscore));   
    }

    ofs.close();
    return true;
}
