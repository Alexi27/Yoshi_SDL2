#include "prototypes.h"


Input input;



int main(int argc, char *argv[])
{
    //unsigned int frameLimit = SDL_GetTicks() + 16;
    int go;

    init("YOSHI");
    loadGame();
    initializePlayer(1);
    atexit(cleanup);
    go = 1;

    while (go == 1)
    {
        getInput(&input);
        updatePlayer(&input);
        drawGame();
    }
    exit(0);
}
