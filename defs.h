#ifndef DEF_DEFS
#define DEF_DEFS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>

/* On inclut les libs supplémentaires */
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

// Taille de la fenêtre : 800x480 pixels
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 480


/* Taille maxi de la map : 400 x 150 tiles */
#define MAX_MAP_X 400
#define MAX_MAP_Y 150

/* Taille d'une tile (32 x 32 pixels) */
#define TILE_SIZE 32

/* Constantes pour l'animation */
#define TIME_BETWEEN_2_FRAMES 20
#define TIME_BETWEEN_2_FRAMES_PLAYER 10

/* Taille du sprite*/
#define PLAYER_WIDTH 37
#define PLAYER_HEIGTH 42

//Vitesse de déplacement en pixels du sprite
#define PLAYER_SPEED 4

//Valeurs attribuées aux états/directions
#define IDLE 0
#define WALK 1
#define JUMP1 2
#define JUMP2 3
#define ATTACK 4


#define RIGHT 1
#define LEFT 2


//Constante pour les limites de la caméra avant scrolling
#define LIMITE_X 400
#define LIMITE_Y 220
#define LIMITE_W 100
#define LIMITE_H 80

//Constantes définissant la gravité et la vitesse max de chute
#define GRAVITY_SPEED 0.6
#define MAX_FALL_SPEED 15
#define JUMP_HEIGHT 10


#define BLANK_TILE 100
#define TILE_TRAVERSABLE 0

#endif
