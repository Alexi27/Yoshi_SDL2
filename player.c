#include "prototypes.h"



int level;
GameObject player;
SDL_Texture *playerSpriteSheet;


GameObject *getPlayer(void)
{
    return &player;
}
int getPlayerx(void)
{
    return player.x;
}
int getPlayery(void)
{
    return player.y;
}
void setPlayerx(int valeur)
{
    player.x = valeur;
}
void setPlayery(int valeur)
{
    player.y = valeur;
}


int getLevel(void)
{
    return level;
}

void SetValeurDuNiveau(int valeur)
{
    level = valeur;
}

void initPlayerSprites(void)
{
    playerSpriteSheet = loadImage("graphics/yoshi.png");
}
void cleanPlayer(void)
{
    if (playerSpriteSheet != NULL)
    {
        SDL_DestroyTexture(playerSpriteSheet);
        playerSpriteSheet = NULL;
    }
}

void initializePlayer(int newLevel)
{
    player.direction = RIGHT;
    player.etat = IDLE;
    player.frameNumber = 0;
    player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
    player.frameMax = 8;
    player.x = getBeginX();
    player.y = getBeginY();

    if (newLevel == 1)
    {
        setStartX(getBeginX());
        setStartY(getBeginY());
    }
    player.w = PLAYER_WIDTH;
    player.h = PLAYER_HEIGTH;
    player.onGround = 0;

}

void drawPlayer(void)
{

    if (player.frameTimer <= 0)
    {
        player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
        player.frameNumber++;

        if (player.frameNumber >= player.frameMax)
            player.frameNumber = 0;
    }
    else
        player.frameTimer--;

    SDL_Rect dest;
    dest.x = player.x - getStartX();
    dest.y = player.y - getStartY();
    dest.w = player.w;
    dest.h = player.h;

    SDL_Rect src;

    src.x = player.frameNumber * player.w;
    src.w = player.w;
    src.h = player.h;
    src.y = player.etat * player.h;

    if (player.direction == LEFT)
        SDL_RenderCopyEx(getrenderer(), playerSpriteSheet, &src, &dest, 0, 0, SDL_FLIP_HORIZONTAL);
    else
        SDL_RenderCopyEx(getrenderer(), playerSpriteSheet, &src, &dest, 0, 0, SDL_FLIP_NONE);

}

void updatePlayer(Input *input)
{
    player.dirX = 0;
    player.dirY += GRAVITY_SPEED;
    if (player.dirY >= MAX_FALL_SPEED)
        player.dirY = MAX_FALL_SPEED;
    if (input->left == 1)
    {
        player.dirX -= PLAYER_SPEED;
        player.direction = LEFT;
        if (player.etat != WALK && player.onGround == 1)
        {
            player.etat = WALK;
            player.frameNumber = 0;
            player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
            player.frameMax = 8;
        }
    }

    else if (input->right == 1)
    {
        player.dirX += PLAYER_SPEED;
        player.direction = RIGHT;
        if (player.etat != WALK && player.onGround == 1)
        {
            player.etat = WALK;
            player.frameNumber = 0;
            player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
            player.frameMax = 10;
        }
    }

    else if (input->right == 0 && input->left == 0 && player.onGround == 1)
    {

        if (player.etat != IDLE)
        {
            player.etat = IDLE;
            player.frameNumber = 0;
            player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
            player.frameMax = 4;
        }
    }
    if (input->jump == 1)
    {
        if (player.onGround == 1)
        {
            player.dirY = -JUMP_HEIGHT;
            player.onGround = 0;
            player.jump = 1;
        }
        // Si on est en saut 1, on peut faire un deuxième bond et on remet jump1 à 0
        else if (player.jump == 1)
        {
            player.dirY = -JUMP_HEIGHT;
            player.jump = 0;
        }
        input->jump = 0;
    }

    // Réactive la possibilité de double saut si on tombe sans sauter */
    if (player.onGround == 1)
        player.jump = 1;


    if (player.onGround == 0)
    {
//Si on est en saut 1, on met l'anim' du saut normal
        if (player.jump == 1)
        {
            if (player.etat != JUMP1)
            {
                player.etat = JUMP1;
                player.frameNumber = 0;
                player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
                player.frameMax = 4;
            }
        }
        else
        {
            if (player.etat != JUMP2)
            {
                player.etat = JUMP2;
                player.frameNumber = 0;
                player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
                player.frameMax = 8;
            }
        }
    }
    mapCollision(&player);
    centerScrollingOnPlayer();
}

void centerScrollingOnPlayer(void)
{
    int cxperso = player.x + player.w / 2;
    int cyperso = player.y + player.h / 2;
    int xlimmin = getStartX() + LIMITE_X;
    int xlimmax = xlimmin + LIMITE_W;
    int ylimmin = getStartY() + LIMITE_Y;
    int ylimmax = ylimmin + LIMITE_H;

    if (cxperso < getStartX())
    {
        setStartX(getStartX() - 30);
    }
    else if (cxperso < xlimmin)
    {
        setStartX(getStartX() - 4);
    }
    if (cxperso > getStartX() + SCREEN_WIDTH)
    {
        setStartX(getStartX() + 30);
    }
    else if (cxperso > xlimmax)
    {
        setStartX(getStartX() + 4);
    }
    if (getStartX() < 0)
    {
        setStartX(0);
    }
    else if (getStartX() + SCREEN_WIDTH >= getMaxX())
    {
        setStartX(getMaxX() - SCREEN_WIDTH);
    }
    if (cyperso < ylimmin)
    {
        setStartY(getStartY() - 4);
    }
    if (cyperso > ylimmax)
    {
        if (player.dirY >= MAX_FALL_SPEED - 2)
        {
            setStartY(getStartY() + MAX_FALL_SPEED + 1);
        }
        else
        {
            setStartY(getStartY() + 4);
        }
    }
    if (getStartY() < 0)
    {
        setStartY(0);
    }
    else if (getStartY() + SCREEN_HEIGHT >= getMaxY())
    {
        setStartY(getMaxY() - SCREEN_HEIGHT);
    }

}
