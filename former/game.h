#include "./board.h"
#include "./piece.h"
#include <random>
#include "IO.h"

class Game {
  private:
    int screenHeight;
    Board *board;
    Piece *currPiece;
    Piece *nextPiece;
    IO *io;

    int getRand(int inf, int sup);
    void initGame();
    void drawPiece(Piece &piece);
    void drawBoard();

  public:
    Game(Board *board, Piece *pieces, IO *io, int screenHeight);

    void drawScene();
    void createNewPiece();
};