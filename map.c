#include "prototypes.h"

Map map;

void loadMap(char *name)
{
    int x, y;
    FILE *fp;
    fp = fopen(name, "rb");
    if (fp == NULL)
    {
        printf("Failed to open map");
        exit(1);
    }
    fscanf(fp, "%d", &map.beginx);
    fscanf(fp, "%d", &map.beginy);

    fscanf(fp, "%d", &map.tilesetAffiche);

    map.maxX = map.maxY = 0;

    for (y = 0; y < MAX_MAP_Y; y++)
    {
        for (x = 0; x < MAX_MAP_X; x++)
        {
            fscanf(fp, "%d", &map.tile[y][x]);

            if (map.tile[y][x] > 0)
            {
                if (x > map.maxX)
                {
                    map.maxX = x;
                }

                if (y > map.maxY)
                {
                    map.maxY = y;
                }
            }
        }
    }

    map.maxX = (map.maxX + 1) * TILE_SIZE;
    map.maxY = (map.maxY + 1) * TILE_SIZE;

    fclose(fp);

}
void drawMap(int layer)
{
    int x, y, mapX, x1, x2, mapY, y1, y2, xsource, ysource, a;


    mapX = map.startX / TILE_SIZE;

    // Coordonn�es de d�part pour l'affichage de la map
    //permet de d�terminer � quels coordonn�es blitter la 1�re colonne de tiles au pixel pr�s
    x1 = (map.startX % TILE_SIZE) * -1;

    // coordonn�es de la fin de la map
    //on doit aller � x1 (d�part) + SCREEN_WIDTH (la largeur de l'�cran)+1 si on a commencer avant l'ecran.
    x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

    mapY = map.startY / TILE_SIZE;
    y1 = (map.startY % TILE_SIZE) * -1;
    y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

    // On dessine ligne par ligne
    if (layer == 1)
    {
        for (y = y1; y < y2; y += TILE_SIZE)
        {
            /* A chaque d�but de ligne, on r�initialise mapX qui contient la colonne
            (0 au d�but puisqu'on ne scrolle pas) */
            mapX = map.startX / TILE_SIZE;

            // A chaque colonne de tile, on dessine la bonne tile en allant de x = 0 � x = 640

            for (x = x1; x < x2; x += TILE_SIZE)
            {
                a = map.tile[mapY][mapX];

                // 10 est la largeur du tileset
                ysource = a / 10 * TILE_SIZE;
                xsource = a % 10 * TILE_SIZE;

                // on blitte la bonne tile au bon endroit

                drawTile(map.tileSet, x, y, xsource, ysource);

                mapX++;
            }

            mapY++;
        }
    }

}

void changeLevel(void)
{

    char file[200];

    /* Charge la map depuis le fichier */
    sprintf(file, "map/map%d.txt", getLevel());
    loadMap(file);

//Charge le tileset
    if (map.tileSet != NULL)
    {
        SDL_DestroyTexture(map.tileSet);
    }
    //if (map.tileSetB != NULL)
    //{
    //    SDL_DestroyTexture(map.tileSetB);
    //}

    sprintf(file, "graphics/tileset%d.png", map.tilesetAffiche);
    map.tileSet = loadImage(file);

    // sprintf(file, "graphics/tileset%dB.png", map.tilesetAffiche);
    // map.tileSetB = loadImage(file);

}

void cleanMaps(void)
{
// Lib�re la texture du background
    if (map.background != NULL)
    {
        SDL_DestroyTexture(map.background);
        map.background = NULL;
    }

// Lib�re les textures des tilesets
    if (map.tileSet != NULL)
    {
        SDL_DestroyTexture(map.tileSet);
        map.tileSet = NULL;
    }


}

int getStartX(void)
{
    return map.startX;
}

void setStartX(int valeur)
{
    map.startX = valeur;
}

int getStartY(void)
{
    return map.startY;
}

void setStartY(int valeur)
{
    map.startY = valeur;
}

int getMaxX(void)
{
    return map.maxX;
}

int getMaxY(void)
{
    return map.maxY;
}

int getBeginX(void)
{
    return map.beginx;
}

int getBeginY(void)
{
    return map.beginy;
}



void mapCollision(GameObject *entity)
{

    int i, x1, x2, y1, y2;

    /* D'abord, on consid�re le joueur en l'air jusqu'� temps
    d'�tre s�r qu'il touche le sol */
    entity->onGround = 0;

    /* Ensuite, on va tester les mouvements horizontaux en premier
    (axe des X). On va se servir de i comme compteur pour notre boucle.
    En fait, on va d�couper notre sprite en blocs de tiles pour voir
    quelles tiles il est susceptible de recouvrir.
    On va donc commencer en donnant la valeur de Tile_Size � i pour qu'il
    teste la tile o� se trouve le x du joueur mais aussi la suivante SAUF
    dans le cas o� notre sprite serait inf�rieur � la taille d'une tile.
    Dans ce cas, on lui donnera la vraie valeur de la taille du sprite
    Et on testera ensuite 2 fois la m�me tile. Mais comme �a notre code
    sera op�rationnel quelle que soit la taille de nos sprites ! */

    if (entity->h > TILE_SIZE)
        i = TILE_SIZE;
    else
        i = entity->h;


//On lance alors une boucle for infinie car on l'interrompra selon
//les r�sultats de nos calculs
    for (;;)
    {
//On va calculer ici les coins de notre sprite � gauche et �
//droite pour voir quelle tile ils touchent.
        x1 = (entity->x + entity->dirX) / TILE_SIZE;
        x2 = (entity->x + entity->dirX + entity->w - 1) / TILE_SIZE;

//M�me chose avec y, sauf qu'on va descendre au fur et � mesure
//pour tester toute la hauteur de notre sprite, gr�ce � notre
//fameuse variable i.
        y1 = (entity->y) / TILE_SIZE;
        y2 = (entity->y + i - 1) / TILE_SIZE;

        if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
        {
//Si on a un mouvement � droite
            if (entity->dirX > 0)
            {
                if (map.tile[y1][x2] > BLANK_TILE || map.tile[y2][x2] > BLANK_TILE)
                {


                    entity->x = x2 * TILE_SIZE;
                    entity->x -= entity->w + 1;
                    entity->dirX = 0;

                }
            }

//M�me chose � gauche
            else if (entity->dirX < 0)
            {
                if (map.tile[y1][x1] > BLANK_TILE || map.tile[y2][x1] > BLANK_TILE)
                {
                    entity->x = (x1 + 1) * TILE_SIZE;
                    entity->dirX = 0;
                }

            }

        }

//On sort de la boucle si on a test� toutes les tiles le long de la hauteur du sprite.
        if (i == entity->h)
        {
            break;
        }

//Sinon, on teste les tiles sup�rieures en se limitant � la heuteur du sprite.
        i += TILE_SIZE;

        if (i > entity->h)
        {
            i = entity->h;
        }
    }


//On recommence la m�me chose avec le mouvement vertical (axe des Y)
    if (entity->w > TILE_SIZE)
        i = TILE_SIZE;
    else
        i = entity->w;


    for (;;)
    {
        x1 = (entity->x) / TILE_SIZE;
        x2 = (entity->x + i) / TILE_SIZE;

        y1 = (entity->y + entity->dirY) / TILE_SIZE;
        y2 = (entity->y + entity->dirY + entity->h) / TILE_SIZE;

        if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
        {
            if (entity->dirY > 0)
            {
                /* D�placement en bas */


                if (map.tile[y2][x1] > TILE_TRAVERSABLE || map.tile[y2][x2] > TILE_TRAVERSABLE)
                {

                    entity->y = y2 * TILE_SIZE;
                    entity->y -= entity->h;
                    entity->dirY = 0;
                    entity->onGround = 1;
                }

            }

            else if (entity->dirY < 0)
            {

                if (map.tile[y1][x1] > BLANK_TILE || map.tile[y1][x2] > BLANK_TILE)
                {
                    entity->y = (y1 + 1) * TILE_SIZE;
                    entity->dirY = 0;
                }

            }
        }

//On teste la largeur du sprite (m�me technique que pour la hauteur pr�c�demment)
        if (i == entity->w)
        {
            break;
        }

        i += TILE_SIZE;

        if (i > entity->w)
        {
            i = entity->w;
        }
    }

    entity->x += entity->dirX;
    entity->y += entity->dirY;

    if (entity->x < 0)
    {
        entity->x = 0;
    }

    else if (entity->x + entity->w >= map.maxX)
    {
//Si on touche le bord droit de l'�cran, on annule
//et on limite le d�placement du joueur
        entity->x = map.maxX - entity->w - 1;
    }


}
