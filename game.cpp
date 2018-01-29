#include "./game.h"
#include "./model.h"
#include "./view.h"

Game::Game(Model *m, View &v) : view(v) {
    model = m;
    view.setControler(this, m);

    srand((unsigned)time(NULL));

    currPiece = new Piece();
    nextPiece = new Piece();
    nextPiece->setX(NEXTPIECE_X);
    nextPiece->setY(NEXTPIECE_Y);

    board = (int **)malloc(BOARD_WIDTH * sizeof(int *));
    for (unsigned i = 0; i < BOARD_WIDTH; i++)
        board[i] = (int *)malloc(BOARD_HEIGHT * sizeof(int));

    for (unsigned i = 0; i < BOARD_WIDTH; i++)
        for (unsigned j = 0; j < BOARD_HEIGHT; j++)
            board[i][j] = BOARD_FREE;

    score = 0;
    nbLines = 0;
    level = 0;
}

int Game::GetRandom(int inf, int sup) { return rand() % (sup - inf + 1) + inf; }

void Game::launch() {
    model->loadTiles();
    int ofepzfzea = 0;

    setupNextPiece();
    sf::RenderWindow *window = view.createWindow();
    sf::Clock timer;

    while (window->isOpen()) {
        window->clear(sf::Color::White);
        view.drawBoard(board);
        view.drawPiece(*currPiece);
        view.drawPiece(*nextPiece);
        view.drawText(TEXT_SCORE_X, TEXT_SCORE_Y, "SCORE");
        view.drawText(TEXT_LEVEL_X, TEXT_LEVEL_Y, "LEVEL");
        view.drawText(TEXT_LINE_X, TEXT_LINE_Y, "LINES");
        window->display();

        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();

            if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::Return && canRotate()) {
                    currPiece->rotate();
                } else if (event.key.code == sf::Keyboard::Left &&
                           canMoveLeft()) {
                    currPiece->moveLeft();
                } else if (event.key.code == sf::Keyboard::Right &&
                           canMoveRight()) {
                    currPiece->moveRight();
                } else if (event.key.code == sf::Keyboard::Down &&
                           canMoveDown()) {
                    currPiece->moveDown();
                }
        }

        auto elapsed = timer.getElapsedTime().asMilliseconds();
        if (elapsed > WAIT_TIME) {
            if (canMoveDown()) {
                currPiece->moveDown();
            } else {
                storePieceOnBoard();

                deleteLine();

                if (isGameOver())
                    return;

                setupNextPiece();
            }
            timer.restart();
        }
    }
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
    default:
        score += (level + 1) * 1200;
        break;
    }
    
    if((nbLines % 10) > ((nbLines + line) % 10))
        increaseLevel();
    
    nbLines += line;
}

void Game::increaseLevel() { level = (level == MAX_LEVEL) ? level : level + 1; }

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
    for (unsigned i = 0; i < SIZE_PIECE_SHAPE; i++)
        if (board[i][0] != BOARD_FREE)
            return true;

    return false;
}
