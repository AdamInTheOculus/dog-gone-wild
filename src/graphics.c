/**
 * @file graphics.c
 * @author Adam Sinclair
 * @created Tues March 27 2018
 * @purpose Contains definitions of Graphics functions
**/

#include "graphics.h"
#include "debug.h"

#define IMAGE_COUNT 50

Graphics initializeGraphics(const int width, const int height)
{
    Graphics g;
    g.width = width;
    g.height = height;

    int errorCode = SDL_CreateWindowAndRenderer(
        width, 
        height, 
        0,
        &g.window,
        &g.renderer
    );

    if(errorCode)
        log_error_exit("%s\n", SDL_GetError());

    SDL_SetWindowTitle(g.window, "Dog Gone Wild");
    return g;
}

void destroyGraphics(Graphics* g)
{
    SDL_DestroyWindow(g->window);
    return;
}