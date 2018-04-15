#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "HashTableAPI.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct Graphics {
    int width;
    int height;
    SDL_Window* window;
    SDL_Renderer* renderer;

    HashTable spriteManager;
} Graphics;

Graphics initializeGraphics(int width, int height);
void destroyGraphics(Graphics* g);

// ======================
// ==  Image Handling  ==
// ======================

/** SDL_Surface* loadImage()
 * @purpose Loads image into spritesheet, if it doesn't already exist.
 * @param `file` Relative path to image file.
 * @return 
**/
SDL_Surface* loadImage(HashTable* spriteManager, char* filePath);

/** void blitSurface()
 * Draw a texutre to certain part of screen
**/
void blitSurface(Graphics* g, SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* destRect);

/** void render()
 * Render everything to screen
**/
void render();

/** void clear()
 * Clears entire screen
**/
void clear();

#endif
