#ifndef DEF_STRUCTS
#define DEF_STRUCTS

#include "defs.h"

typedef struct Input
{

    int left, right, up, down, jump, attack, enter, erase, pause;

} Input;

typedef struct Map
{

    SDL_Texture *background;
    SDL_Texture *tileSet;

    int tilesetAffiche;
    int beginx, beginy;
    int startX, startY;
    int maxX, maxY;

    int tile[MAX_MAP_Y][MAX_MAP_X];

} Map;

typedef struct GameObject
{
    int x, y;
    int h, w;

    int frameNumber, frameTimer, frameMax;
    int etat, direction;
    int onGround;
    float dirX, dirY;
    int saveX, saveY;
    int jump;

} GameObject;

#endif
