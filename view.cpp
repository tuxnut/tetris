#include "./view.h"
#include "./model.h"

void View::setControler(Game *game, Model *m) {
    controler = game;
    model = m;
}

sf::RenderWindow *View::createWindow() {
    window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tetris");
    window->setFramerateLimit(FPS);
    font.loadFromFile("./res/Roboto-Regular.ttf");
    return window;
}

sf::RenderWindow *View::getWindow() {
    return window;
}

void View::drawTile(int px, int py, enum Tile color) {
    sf::Sprite sprite = model->getTileSprite(color);
    sprite.setPosition(px, py);
    window->draw(sprite);
}

void View::drawPiece(Piece &piece) {
    int px = piece.getX();
    int py = piece.getY();
    int kind = piece.getKind();
    int variation = piece.getVariation();
    enum Tile color = piece.getColor();


    for(unsigned i = 0; i < SIZE_PIECE_SHAPE; i++)
        for(unsigned j = 0; j < SIZE_PIECE_SHAPE; j++)
            if(shape[kind][variation][j][i] != 0)
                drawTile(BOARD_X + (px + i) * TILE_SIZE, BOARD_Y + (py + j) * TILE_SIZE, color);
}

void View::drawText(int px, int py, std::string text) {
    sf::Text t;

    t.setFont(font);
    t.setString(text);
    t.setPosition(px, py);
    t.setCharacterSize(14);
    t.setColor(sf::Color::Black);
    window->draw(t);
}

void View::drawBoard(int **board) {
    window->clear(sf::Color::White);
    
    for(unsigned i = 0; i < BOARD_WIDTH + 2; i++) {
        drawTile(PADDING + i * TILE_SIZE, PADDING, BLACK);
        drawTile(PADDING + i * TILE_SIZE, BOARD_Y + BOARD_HEIGHT * TILE_SIZE, BLACK);
    }
    for(unsigned i = 0; i < BOARD_HEIGHT; i++) {
        drawTile(PADDING, BOARD_Y + i * TILE_SIZE, BLACK);
        drawTile((BOARD_X + BOARD_WIDTH * TILE_SIZE), BOARD_Y + i * TILE_SIZE, BLACK);
    }

    for(unsigned i = 0; i < BOARD_WIDTH; i++)
        for(unsigned j = 0; j < BOARD_HEIGHT; j++)
            if (board[i][j] != BOARD_FREE)
                drawTile(BOARD_X + i* TILE_SIZE, BOARD_Y + j * TILE_SIZE, IntToTile(board[i][j]));

    drawText(TEXT_SCORE_X, TEXT_SCORE_Y, "SCORE");
    drawText(TEXT_SCORE_X + 20, TEXT_SCORE_Y + 20, std::to_string(controler->getScore()));
    drawText(TEXT_LEVEL_X, TEXT_LEVEL_Y, "LEVEL");
    drawText(TEXT_LEVEL_X + 20, TEXT_LEVEL_Y + 20, std::to_string(controler->getLevel()));
    drawText(TEXT_LINE_X, TEXT_LINE_Y, "LINES");
    drawText(TEXT_LINE_X + 20, TEXT_LINE_Y + 20, std::to_string(controler->getLines()));
    drawText(TEXT_NEXT_X, TEXT_NEXT_Y, "NEXT");
}

void View::drawPause() {
    drawText(TEXT_PAUSE_X, TEXT_PAUSE_Y, "PAUSE");
}

void View::drawHighscore(const std::vector<Highscore> &hs, int place) {
    window->clear(sf::Color::White);

    int rowSize = (WINDOW_WIDTH - 2 * PADDING) / TILE_SIZE;
    int colSize = (WINDOW_HEIGHT - 2 * PADDING) / TILE_SIZE;
    for(int i = 0; i < rowSize; i++) {
        drawTile(PADDING + i * TILE_SIZE, PADDING, BLACK);
        drawTile(PADDING + i * TILE_SIZE, WINDOW_HEIGHT - PADDING - TILE_SIZE, BLACK);
    }
    for(int i = 0; i < colSize; i++) {
        drawTile(PADDING, PADDING + i * TILE_SIZE, BLACK);
        drawTile(WINDOW_WIDTH - PADDING - TILE_SIZE, PADDING + i * TILE_SIZE, BLACK);
    }
    for (int i = 0; i < hs.size(); i++) {
        std::string name = std::to_string(hs[i].ladder) + ". ";
        name += (place == i + 1) ? "" : hs[i].player;
        std::string points = std::to_string(hs[i].score);

        drawText(BOARD_X + 50, PADDING + 2 * (i + 1) * TILE_SIZE, name);
        drawText(BOARD_X + 220, PADDING + 2 * (i + 1) * TILE_SIZE, points);
    }
}

void View::drawPlayerNameOnHighscore(int place, std::string name) {
    drawText(BOARD_X + 50 + 14, PADDING + 2 * place * TILE_SIZE, name);
}
