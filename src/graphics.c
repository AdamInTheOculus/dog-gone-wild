/**
 * @file graphics.c
 * @author Adam Sinclair
 * @created Tues March 27 2018
 * @purpose Contains definitions of Graphics functions
**/

#include "graphics.h"
#include "debug.h"

#define IMAGE_COUNT 25


/**
 * HashTable functions for handling SDL_Surface* data.
 * Might switch to different type later, but for now I'll leave this here.
**/
char* printSurface(void* toBePrinted);
void deleteSurface(void* toBeDeleted);
int compareSurfaces(const void* first, const void* second);

Graphics initializeGraphics(const int width, const int height)
{
    Graphics g;
    g.width = width;
    g.height = height;
    g.spriteManager = initializeHashTable(IMAGE_COUNT, &printSurface, &deleteSurface, &compareSurfaces);

    int errorCode = SDL_CreateWindowAndRenderer(
        width, 
        height, 
        0,
        &g.window,
        &g.renderer
    );

    if(errorCode)
    {
        deleteHashTable(&g.spriteManager);
        log_error_exit("%s\n", SDL_GetError());
    }

    SDL_SetWindowTitle(g.window, "Dog Gone Wild");
    return g;
}

void destroyGraphics(Graphics* g)
{
    deleteHashTable(&g->spriteManager);
    SDL_DestroyWindow(g->window);
    return;
}

/** SDL_Surface* loadImage()
 * @purpose Loads image into spritesheet, if it doesn't already exist.
 * @param `file` Relative path to image file.
 * @return Image from HashTable regardless if it was inserted or not.
**/
SDL_Surface* loadImage(HashTable* spriteManager, char* filePath)
{
    if(spriteManager == NULL || filePath == NULL || strlen(filePath) < 1)
    {
        log_error("%s", "Could not load image. SpriteManager or path is NULL.\n");
        return NULL;
    }

    // If already exists, return the image.
    void* entry = NULL;
    if((entry = getEntry(spriteManager, filePath)) != NULL)
        return (SDL_Surface*)entry;

    // Otherwise attempt to generate a new image.
    SDL_Surface* surface = IMG_Load(filePath);
    if(surface == NULL)
    {
        log_error("Failed to load image with path [%s]. %s\n", filePath, SDL_GetError());
        return NULL;
    }

    // Attempt to insert image into HashTable.
    if(insertEntry(spriteManager, filePath, (void*)surface) == false)
    {
        log_error("File [%s] failed to insert into HashTable.\n", filePath);
        SDL_FreeSurface(surface);
        return NULL;
    }

    return surface;
}

/** void blitSurface()
 * Draw a texutre to certain part of screen
**/
void blitSurface(Graphics* g, SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* destRect)
{
    if(g == NULL || texture == NULL || srcRect == NULL || destRect == NULL)
    {
        log_error("%s", "Could not blit surface. A parameter is NULL.\n");
        return;
    }

    SDL_RenderCopy(g->renderer, texture, srcRect, destRect);
}

/** void render()
 * Render everything to screen
**/
void render(Graphics* g)
{
    if(g == NULL)
    {
        log_error("%s", "Could not render. Graphics pointer is NULL.\n");
        return;
    }

    SDL_RenderPresent(g->renderer);
}

/** void clear()
 * Clears entire screen
**/
void clear(Graphics* g)
{
    if(g == NULL)
    {
        log_error("%s", "Could not clear renderer. Graphics pointer is NULL.\n");
        return;
    }

    SDL_RenderClear(g->renderer);
}

/**
 * HashTable functions for handling SDL_Surface* data.
 * Might switch to different type later, but for now I'll leave this here.
**/
char* printSurface(void* toBePrinted)
{
    if(toBePrinted == NULL)
    {
        log_error("%s", "void* data is NULL.\n");
        return NULL;
    }

    SDL_Surface* surface = (SDL_Surface*)toBePrinted;

    char* string = NULL;
    if((string = malloc(sizeof(char) * 100)) == NULL)
    {
        log_error("%s", "Failed to malloc 100 bytes to `string`.\n");
        return NULL;
    }

    sprintf(string, 
        "SDL_Surface -- Width [%d], Height [%d], Pitch [%d], Pixel address [%p]\n",
        surface->w, surface->h, surface->pitch, surface->pixels
    );

    return string;
}

void deleteSurface(void* toBeDeleted)
{
    if(toBeDeleted == NULL)
    {
        log_error("%s", "void* data is NULL.\n");
        return;
    }

    SDL_Surface* surface = (SDL_Surface*)toBeDeleted;
    SDL_FreeSurface(surface);
    return;
}

int compareSurfaces(const void* first, const void* second)
{
    if(first == NULL) {
        log_error("%s", "void* first is NULL.\n");
        return -2;
    } else if(second == NULL) {
        log_error("%s", "void* second is NULL.\n");
        return -2;
    }

    if(first == second) // They point to the same address
        return 0;
    else
        return 1;
}
