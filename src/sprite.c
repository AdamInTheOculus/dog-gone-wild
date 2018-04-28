#include "sprite.h"
#include "debug.h"

#define SPRITE_SCALE 2

Sprite createSprite(Graphics* g, char* filePath, int srcX, int srcY, int width, int height, 
                    float posX, float posY, void (*deleteSprite)(Sprite*), void(*updateSprite)(Sprite*))
{
    if(g == NULL)
        log_error_exit("Graphics pointer [%p] is NULL.\n", g);
    if(filePath == NULL || strlen(filePath) < 1)
        log_error_exit("File [%s] is empty or NULL.\n", filePath);
    // if(deleteSprite == NULL)
    //     log_error_exit("%s", "deleteSprite(Sprite*) function is NULL.\n");
    // if(updateSprite == NULL)
    //     log_error_exit("%s", "updateSprite(Sprite*) function is NULL.\n");

    Sprite s;
    s.delete = deleteSprite;
    s.update = updateSprite;
    s.srcRect.x = srcX;
    s.srcRect.y = srcY;
    s.srcRect.w = width;
    s.srcRect.h = height;
    s.x = posX;
    s.y = posY;

    s.spriteSheet = SDL_CreateTextureFromSurface(g->renderer, loadImage(&g->spriteManager, filePath));
    if(s.spriteSheet == NULL)
        log_error_exit("Failed to create texture from surface. Filepath [%s].\n", filePath);

    return s;
}

void drawSprite(Graphics* g, Sprite* s, int x, int y)
{
    if(g == NULL)
        log_error_exit("Graphics pointer [%p] is NULL.\n", g);
    if(s == NULL)
        log_error_exit("Sprite pointer [%p] is NULL.\n", s);


    SDL_Rect destRect = { 
        x, 
        y, 
        s->srcRect.w * SPRITE_SCALE, 
        s->srcRect.h * SPRITE_SCALE
    };

    blitSurface(g, s->spriteSheet, &s->srcRect, &destRect);
}

