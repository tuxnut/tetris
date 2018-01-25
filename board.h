#include "./piece.h"

class Board {
  private:
    enum { FREE, FILLED };
    int mBoard[BOARD_HEIGHT][BOARD_WIDTH];
    Piece *currPiece;

    void initBoard();
    void deleteLine(int line);

  public:
    Board();
    Board(Piece *pieces);

    bool isPositionFree(int posX, int posY);
    void deletePossibleLines();
    bool isGameOver();
    void computeShape(int posX, int posY);
};