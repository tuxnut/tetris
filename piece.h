#include "./constant.h"

class Piece {
  private:
    Point position; // on the board
    int kind;       // kind of piece
    int variation;  // current rotation of piece

  public:
    Point getPosition();
    void setPosition(Point p);

    int getKind();
    void setKind(int k);

    int getVariation();
    void setVariation(int v);

    int getBlockAt(int posX, int posY);
};