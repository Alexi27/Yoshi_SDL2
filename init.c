#include "prototypes.h"


SDL_Window *screen;
SDL_Renderer *renderer;


SDL_Renderer *getrenderer(void)
{
    return renderer;
}


void init(char *title)
{
    screen = SDL_CreateWindow(title,
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_PRESENTVSYNC);

    if (screen == NULL || renderer == NULL)
    {
        printf("Impossible d'ouvrir le jeu");
        exit(1);
    }

    //On cache le curseur de la souris
    SDL_ShowCursor(SDL_DISABLE);

}

void loadGame(void)
{
    initPlayerSprites();
    SetValeurDuNiveau(1);
    changeLevel();
}


void cleanup()
{
    cleanMaps();
    cleanPlayer();
    SDL_Quit();
}
