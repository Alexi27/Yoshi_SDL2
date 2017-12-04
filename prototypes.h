#ifndef PROTOTYPES
#define PROTOTYPES

#include "structs.h"

/* Catalogue des prototypes des fonctions utilisées.
On le complétera au fur et à mesure. */

extern void centerScrollingOnPlayer(void);
extern void changeLevel(void);
extern void cleanMaps(void);
extern void cleanPlayer(void);
extern void cleanup(void);
extern void delay(unsigned int frameLimit);
extern void drawGame(void);
extern void drawImage(SDL_Texture *, int, int);
extern void drawMap(int);
extern void drawPlayer(void);
extern void drawTile(SDL_Texture *image, int destx, int desty, int srcx, int srcy);
extern void gestionInputs(Input *input);
extern SDL_Texture *getBackground(void);
extern int getBeginX(void);
extern int getBeginY(void);
extern void getInput(Input *input);
extern int getLevel(void);
extern int getMaxX(void);
extern int getMaxY(void);
extern GameObject *getPlayer(void);
extern int getPlayerDirection(void);
extern int getPlayerx(void);
extern int getPlayery(void);
extern SDL_Renderer *getrenderer(void);
extern int getStartX(void);
extern int getStartY(void);
extern void init(char *);
extern void initializePlayer(int newLevel);
extern void initPlayerSprites(void);
extern void loadGame(void);
extern SDL_Texture *loadImage(char *name);
extern void loadMap(char *name);
extern void mapCollision(GameObject *entity);
extern void setNombreDeVies(int valeur);
extern void setNombreDetoiles(int valeur);
extern void setStartX(int valeur);
extern void setStartY(int valeur);
extern void SetValeurDuNiveau(int valeur);
extern void updatePlayer(Input *input);


#endif
