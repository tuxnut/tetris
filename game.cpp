#include "./game.h"
#include "./model.h"
#include "./view.h"

Game::Game(Model *m, View &v) : view(v) {
    model = m;
    view.setControler(this, m);

    srand((unsigned)time(NULL));

    currPiece = new Piece();
    nextPiece = new Piece();
    setupNextPiece();

    model->loadMusic(&music, MUSIC_A);
    loadSound();

    board = new int *[BOARD_WIDTH * sizeof(int *)];

    for (unsigned i = 0; i < BOARD_WIDTH; i++)
        board[i] = new int[BOARD_HEIGHT * sizeof(int)];

    for (unsigned i = 0; i < BOARD_WIDTH; i++)
        for (unsigned j = 0; j < BOARD_HEIGHT; j++)
            board[i][j] = BOARD_FREE;

    score = 0;
    nbLines = 0;
    level = 0;
    waitTimer = WAIT_TIME;
    state = HIGHSCORE;
}

int Game::GetRandom(int inf, int sup) { return rand() % (sup - inf + 1) + inf; }

float Game::GetRandom(float inf, float sup) {
    return inf + static_cast<float>(rand()) /
                     (static_cast<float>(RAND_MAX / (sup - inf)));
}

int Game::getScore() { return score; }

int Game::getLines() { return nbLines; }

int Game::getLevel() { return level; }

int Game::getNbPiece() { return nbPiece; }

void Game::launch() {
    model->loadTiles();
    music.setLoop(true);
    // music.play();

    sf::RenderWindow *window = view.createWindow();

    setupNextPiece();

    while (window->isOpen()) {
        switch (state) {
        case PLAYING:
            startGame(window);
            break;
        case MENU:
            break;
        case PAUSED:
            pauseGame(window);
            break;
        case HIGHSCORE:
            displayHighscore(window);
            break;
        case QUITING:
            window->close();
            break;
        }
    }
}

void Game::startGame(sf::RenderWindow *window) {
    window->clear(sf::Color::White);
    std::cout << __LINE__ << std::endl;
    view.drawBoard(board);
    std::cout << __LINE__ << std::endl;
    view.drawPiece(*currPiece);
    std::cout << __LINE__ << std::endl;
    view.drawPiece(*nextPiece);
    std::cout << __LINE__ << std::endl;
    window->display();

    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            finishGame();
            deleteBoard();
            window->close();
        }
        if (event.type == sf::Event::KeyPressed)
            if (event.key.code == sf::Keyboard::Return && canRotate()) {
                playSound(ROTATE);
                currPiece->rotate();
            } else if (event.key.code == sf::Keyboard::Left && canMoveLeft()) {
                playSound(MOVE);
                currPiece->moveLeft();
            } else if (event.key.code == sf::Keyboard::Right &&
                       canMoveRight()) {
                playSound(MOVE);
                currPiece->moveRight();
            } else if (event.key.code == sf::Keyboard::Down && canMoveDown()) {
                playSound(MOVE);
                currPiece->moveDown();
            } else if (event.key.code == sf::Keyboard::Space) {
                state = PAUSED;
            } else if (event.key.code == sf::Keyboard::A) {
                state = HIGHSCORE;
            } else if (event.key.code == sf::Keyboard::Escape) {
                finishGame();
                state = QUITING;
                return;
            }
    }

    auto elapsed = timer.getElapsedTime().asMilliseconds();
    if (elapsed > waitTimer) {
        if (canMoveDown()) {
            // playSound(MOVE);
            currPiece->moveDown();
        } else {
            playSound(PIECE_FALLEN);
            storePieceOnBoard();

            deleteLine();

            if (isGameOver()) {
                playSound(GATE_CLOSE);
                playSound(GAMEOVER);
                finishGame();
                state = HIGHSCORE;
                return;
            }
            setupNextPiece();
        }
        timer.restart();
    }
}

void Game::pauseGame(sf::RenderWindow *window) {
    view.drawPause();
    window->display();
    sf::Event event;
    while (window->waitEvent(event)) {
        if (event.type == sf::Event::Closed) {
            finishGame();
            deleteBoard();
            window->close();
        } else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Space) {
                state = PLAYING;
                break;
            } else if (event.key.code == sf::Keyboard::Escape) {
                finishGame();
                state = QUITING;
                break;
            }
        }
    }
}

void Game::displayHighscore(sf::RenderWindow *window) {
    std::vector<Highscore> hs = model->loadHighscores();

    if (hs.size() == 0) {
        state = PLAYING;
        return;
    }

    int place = isHighscore(hs);
    std::string playername = "";

    view.showHighscore(hs, place);

    sf::Event event;
    while (window->waitEvent(event)) {
        view.showHighscore(hs, place);
        view.drawPlayerNameOnHighscore(place, playername);
        window->display();
        if (event.type == sf::Event::Closed) {
            finishGame();
            deleteBoard();
            window->close();
        } else if (event.type == sf::Event::TextEntered && place != -1) {
            if (31 < event.text.unicode && event.text.unicode < 128 &&
                playername.length() < 20) {
                playername += static_cast<char>(event.text.unicode);
            } else if (event.text.unicode == 8 && playername.length() > 0) {
                playername.erase(playername.length() - 1);
            }
        } else if (event.key.code == sf::Keyboard::Return) {
            if (place != -1 && !playername.empty()) {
                model->writeHighscores(hs, playername, place);
                state = PLAYING;
                setupNextPiece();
                return;
            }
        } else if (event.key.code == sf::Keyboard::Escape) {
            state = PLAYING;
            setupNextPiece();
            return;
        }
    }
}

void Game::finishGame() {
    delete currPiece;
    delete nextPiece;
    for (unsigned x = 0; x < BOARD_WIDTH; x++)
        for (unsigned y = 0; y < BOARD_HEIGHT; y++)
            board[x][y] = BOARD_FREE;
}

void Game::deleteBoard() {
    for (unsigned i = 0; i < BOARD_WIDTH; i++)
        delete board[i];
    delete board;
}

void Game::setupNextPiece() {
    // change nextPiece to currPiece
    currPiece->copy(*nextPiece);
    currPiece->setX(BOARD_WIDTH / 2 + PIECE_OFFSET_X);
    currPiece->setY(PIECE_OFFSET_Y);

    // get a new nextPiece
    nextPiece = new Piece();
    nextPiece->setX(NEXTPIECE_X);
    nextPiece->setY(NEXTPIECE_Y);
}

void Game::storePieceOnBoard() {
    int px = currPiece->getX();
    int py = currPiece->getY();
    int kind = currPiece->getKind();
    int variation = currPiece->getVariation();
    int color = TileToInt(currPiece->getColor());

    for (int x = 0; x < SIZE_PIECE_SHAPE; x++)
        for (int y = 0; y < SIZE_PIECE_SHAPE; y++)
            if (shape[kind][variation][y][x] != 0)
                board[px + x][py + y] = color;

    nbPiece++;
}

void Game::deleteLine() {
    int nbLine = 0;

    for (int y = 0; y < BOARD_HEIGHT; y++) {

        int x = 0;
        while (x < BOARD_WIDTH) {
            if (board[x][y] == BOARD_FREE)
                break;
            x++;
        }

        if (x == BOARD_WIDTH) {
            for (int j = y; j > 0; j--)
                for (int i = 0; i < BOARD_WIDTH; i++)
                    board[i][j] = board[i][j - 1];
            nbLine++;
        }
    }

    if (nbLine >= 4) {
        playSound(TETRIS);
    } else if (nbLine > 0) {
        playSound(DELETE_LINE);
    }
    increaseScore(nbLine);
}

void Game::increaseScore(int line) {
    switch (line) {
    case 1:
        score += (level + 1) * 40;
        break;
    case 2:
        score += (level + 1) * 100;
        break;
    case 3:
        score += (level + 1) * 300;
        break;
    case 4:
        score += (level + 1) * 1200;
        break;
    }

    if ((nbLines % 10) > ((nbLines + line) % 10))
        increaseLevel();

    nbLines += line;
}

void Game::increaseLevel() {
    if (level < MAX_LEVEL) {
        level++;
        waitTimer -= 70;
    }
    playSound(LEVELUP);
}

void Game::loadSound() {
    sf::SoundBuffer sb;
    sb = model->loadSound(DELETE_LINE);
    buffers.push_back(sb);
    sb = model->loadSound(MOVE);
    buffers.push_back(sb);
    sb = model->loadSound(ROTATE);
    buffers.push_back(sb);
    sb = model->loadSound(TETRIS);
    buffers.push_back(sb);
    sb = model->loadSound(GATE_CLOSE);
    buffers.push_back(sb);
    sb = model->loadSound(GAMEOVER);
    buffers.push_back(sb);
    sb = model->loadSound(PIECE_FALLEN);
    buffers.push_back(sb);
    sb = model->loadSound(LEVELUP);
    buffers.push_back(sb);
}

void Game::playSound(enum Sound s) {
    // while(sound.getStatus() == sf::Sound::Playing) {
    //     sound.
    //  }
    sound.setBuffer(buffers[s]);
    if (s == MOVE)
        sound.setPitch(GetRandom(1.f, 1.5f));
    else
        sound.setPitch(1);

    sound.play();
}

bool Game::canRotate() {
    int px = currPiece->getX();
    int py = currPiece->getY();
    int kind = currPiece->getKind();
    int variation = (currPiece->getVariation() + 1) % NB_VARIATIONS;

    for (int x = 0; x < SIZE_PIECE_SHAPE; x++)
        for (int y = 0; y < SIZE_PIECE_SHAPE; y++)
            if (shape[kind][variation][y][x] != 0 &&
                (px + x < 0 || px + x >= BOARD_WIDTH || py + y >= BOARD_HEIGHT))
                return false;

    return true;
}

bool Game::canMoveLeft() {
    int px = currPiece->getX() - 1;
    int py = currPiece->getY();
    int kind = currPiece->getKind();
    int variation = currPiece->getVariation();

    for (int x = 0; x < SIZE_PIECE_SHAPE; x++)
        for (int y = 0; y < SIZE_PIECE_SHAPE; y++)
            if (shape[kind][variation][y][x] != 0 &&
                (px + x < 0 || board[px + x][py + y] != BOARD_FREE))
                return false;

    return true;
}

bool Game::canMoveRight() {
    int px = currPiece->getX() + 1;
    int py = currPiece->getY();
    int kind = currPiece->getKind();
    int variation = currPiece->getVariation();

    for (int x = 0; x < SIZE_PIECE_SHAPE; x++)
        for (int y = 0; y < SIZE_PIECE_SHAPE; y++)
            if (shape[kind][variation][y][x] != 0 &&
                (px + x >= BOARD_WIDTH || board[px + x][py + y] != BOARD_FREE))
                return false;

    return true;
}

bool Game::canMoveDown() {
    int px = currPiece->getX();
    int py = currPiece->getY() + 1;
    int kind = currPiece->getKind();
    int variation = currPiece->getVariation();

    for (int x = 0; x < SIZE_PIECE_SHAPE; x++)
        for (int y = 0; y < SIZE_PIECE_SHAPE; y++)
            if (shape[kind][variation][y][x] != 0 &&
                (py + y >= BOARD_HEIGHT || board[px + x][py + y] != BOARD_FREE))
                return false;

    return true;
}

bool Game::isGameOver() {
    for (unsigned i = 0; i < BOARD_WIDTH; i++)
        if (board[i][0] != BOARD_FREE)
            return true;

    return false;
}

int Game::isHighscore(std::vector<Highscore> &hs) {
    int place = -1;

    for (unsigned i = 0; i < hs.size(); i++) {
        if (hs[i].score < score && place == -1) {
            place = i + 1;

            Highscore newHs;
            newHs.ladder = place;
            newHs.score = score;
            strcpy(newHs.player, "");

            hs.emplace(hs.begin() + i, newHs);

            if (hs.size() > 10)
                hs.pop_back();
        } else {
            if (place != -1) {
                hs[i].ladder++;
            }
        }
    }

    return place;
}
