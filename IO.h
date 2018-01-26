#include <SDL2/SDL.h>									
#include "./constant.h"
#include <iostream>

enum color { RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN, GREY, BLACK, WHITE };

class IO {
  public:
    IO();
    
    void drawRectangle(int posX, int posY, int height, int width, enum color col);
    void clearScreen();
    int initGraph();
    int pollKey();
    int getKey();
    bool isKeyDown(int key);
    void updateScreen();
};