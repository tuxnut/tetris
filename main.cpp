#include "./game.h"
#include "./view.h"
#include "./model.h"

int main(int argc, char **argv) {
    View v;
    Model m;
    Game game(&m, v);
    // game.launch();
    m.getHighscores();
    
    return 0;
}
