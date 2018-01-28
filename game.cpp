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
}

int Game::GetRandom(int inf, int sup) { return rand() % (sup - inf + 1) + inf; }

void Game::launch() {
    model->loadTiles();

    setupNextPiece();
    sf::RenderWindow *window = view.createWindow();
    sf::Clock timer;

    while (window->isOpen()) {

        std::cout << timer.restart().asMicroseconds() << std::endl;

        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();

            if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::Return /* && canRotate() */) {
                    currPiece->rotate();
                } else if (event.key.code == sf::Keyboard::Left /* &&
                           canMoveLeft() */) {
                    currPiece->moveLeft();
                } else if (event.key.code == sf::Keyboard::Right) {
                    currPiece->moveRight();
                }
        }
        window->clear(sf::Color::White);
        view.drawBoard(board);

        view.drawPiece(*currPiece);
        view.drawPiece(*nextPiece);
        window->display();
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

void Game::computePieceOnBoard() {
    int px = currPiece->getX();
    int py = currPiece->getY();
    int kind = currPiece->getKind();
    int variation = currPiece->getVariation();

    for (int x = px, i = 0; x < px + SIZE_PIECE_SHAPE; x++, i++)
        for (int y = py, j = 0; y < py + SIZE_PIECE_SHAPE; y++, j++)
            board[x][y] = (shape[kind][variation][i][j] != 0) ? 1 : board[x][y];
}

bool Game::canRotate() {
    int px = currPiece->getX();
    int py = currPiece->getY();
    int kind = currPiece->getKind();
    int rotation = (currPiece->getVariation() == NB_VARIATIONS - 1)
                       ? 0
                       : currPiece->getVariation();

    for (unsigned i = 0; i < SIZE_PIECE_SHAPE; i++) {
        for (unsigned j = 0; j < SIZE_PIECE_SHAPE; j++) {
            if (shape[kind][rotation][i][j] != 0 && board[px + i][py + j]) {
                // if(px + ) {

                // }
            }
        }
    }
}

bool Game::canMoveLeft() {
    int px = currPiece->getX() - 1;
    int py = currPiece->getY();
    int kind = currPiece->getKind();
    int variation = currPiece->getVariation();

    for (int x = px, i = 0; x < px + SIZE_PIECE_SHAPE; x++, i++) {
        for (int y = py, j = 0; y < py + SIZE_PIECE_SHAPE; y++, j++) {
            // check if outside the board
            if (x < 0 && shape[kind][variation][i][j] != 0)
                return false;

            // check collision with other pieces
            if (y >= 0)
                if (shape[kind][variation][i][j] != 0 && board[x][y] != 0)
                    return false;
        }
    }

    return true;
}