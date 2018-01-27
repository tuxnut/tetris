#include "./piece.h"
  enum { FREE, FILLED };

class Board {
  private:
    int mBoard[BOARD_HEIGHT][BOARD_WIDTH];
    Piece *currPiece;

    void initBoard();
    void deleteLine(int line);

  public:
    Board();
    Board(Piece *pieces);

    int getXPosInPixels(int posX);
    int getYPosInPixels(int posY);

    bool isPositionFree(int posX, int posY);
    bool isMovementPossible(int posX, int posY);
    void deletePossibleLines();
    bool isGameOver();
    void computeShape(int posX, int posY);
};
 