#include "./game.h"

int main(int argc, char **argv) {
    
    IO io;
    Piece pieces;
    Board board(&pieces);
    Game game(&board, &pieces, &io, 500);

    auto chrono = SDL_GetTicks();

    while(!io.isKeyDown(SDLK_ESCAPE)) {
        // drawing
        io.clearScreen();   // clearing
        game.drawScene();   // computing where blocks should appear
        io.updateScreen();  // actually putting the graphics blocks on screen

        // input handling
        int keyPressed = io.pollKey();

        switch (keyPressed)
        {
        case SDLK_RIGHT:
            if(board.isMovementPossible()) {
                
            }
            break;
        }
    }

    return 0;
}





// int main(int argc, char **argv) {
//     SDL_Window *window = NULL;

//     SDL_Surface *screenSurface = NULL;

//     if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
//         std::cout << "Error while initializing of SDL" << std::endl;
//     } else {
//         window = SDL_CreateWindow("My Window", SDL_WINDOWPOS_UNDEFINED,
//                                   SDL_WINDOWPOS_UNDEFINED, 320, 480,
//                                   SDL_WINDOW_SHOWN);

//         if (window == NULL) {
//             std::cout << "Error while creating the window" << std::endl;
//         } else {
//             screenSurface = SDL_GetWindowSurface(window);

//             SDL_FillRect(screenSurface, NULL, 0x00000000/* SDL_MapRGB(screenSurface->format, 126, 126, 126) */);

//             SDL_UpdateWindowSurface(window);

//             SDL_Delay(1000);
//         }
//     }

//     SDL_DestroyWindow(window);

//     SDL_Quit();

//     return 0;
// }

///******* Mes test *********///

// class A {
//     public:
//     A() {};
//     A(A &example) { caca = example.caca; };
//     void copy(A &example) { caca = example.caca; };
//     int caca;
// };

// int main(int argc, char **argv) {
//     A *alpha = new A();
//     alpha->caca = 5;

//     A *beta = new A();
//     beta->copy(*alpha);

//     free(alpha);

//     std::cout << beta->caca << std::endl;

//     return 0;
// }
