#include "./game.h"
#include "./view.h"
#include "./model.h"

#include <iostream>

int main(int argc, char **argv) {
    View v;
    Model m;
    Game game(&m, v);
    game.launch();
    return 0;
}