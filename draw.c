#include "prototypes.h"


void drawGame(void)
{
    SDL_Texture *Background = loadImage("graphics/background.png");
    drawImage(Background, 0, 0);
    drawMap(1);
    drawPlayer();
    SDL_RenderPresent(getrenderer());
    // SDL_Delay(1);
}
void drawTile(SDL_Texture *image, int destx, int desty, int srcx, int srcy)
{
    SDL_Rect dest;

    dest.x = destx;
    dest.y = desty;
    dest.w = TILE_SIZE;
    dest.h = TILE_SIZE;

    SDL_Rect src;

    src.x = srcx;
    src.y = srcy;
    src.w = TILE_SIZE;
    src.h = TILE_SIZE;

    SDL_RenderCopy(getrenderer(), image, &src, &dest);
}

SDL_Texture *loadImage(char *name)
{

    SDL_Surface *loadedImage = NULL;
    SDL_Texture *texture = NULL;
    loadedImage = IMG_Load(name);

    if (loadedImage != NULL)
    {
        texture = SDL_CreateTextureFromSurface(getrenderer(), loadedImage);
        SDL_FreeSurface(loadedImage);
        loadedImage = NULL;
    }
    else
        printf("L'image n'a pas pu être chargée! SDL_Error : %s\n", SDL_GetError());

    return texture;

}

void drawImage(SDL_Texture *image, int x, int y)
{
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    SDL_QueryTexture(image, NULL, NULL, &dest.w, &dest.h);
    SDL_RenderCopy(getrenderer(), image, NULL, &dest);
}

