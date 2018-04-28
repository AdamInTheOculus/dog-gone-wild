#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include "graphics.h"

#define SPRITE_SCALE 2

typedef struct Sprite {

    /** 
     * Each Sprite will have its own implementation of Update() and DeleteSprite()
    **/
    void (*delete)(struct Sprite*);
    void (*update)(struct Sprite*);
    float x, y;
    SDL_Rect srcRect;
    SDL_Texture* spriteSheet;

} Sprite;

Sprite createSprite(Graphics* g, char* filePath, int srcX, int srcY, int width, int height, 
    float posX, float posY,void (*deleteSprite)(Sprite*), void(*updateSprite)(Sprite*));

void drawSprite(Graphics* g, Sprite* s, int x, int y);

#endif