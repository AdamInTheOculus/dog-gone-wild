/**
 * @file graphics.c
 * @author Adam Sinclair
 * @created Tues March 27 2018
 * @purpose Contains definitions of Graphics functions
**/

#include "graphics.h"

Graphics initializeGraphics(const int width, const int height)
{
    Graphics g;

    int errorCode = SDL_CreateWindowAndRenderer(
        width, 
        height, 
        0,
        &g.window,
        &g.renderer
    );

    if(errorCode)
        log_error_exit("%s\n", SDL_GetError());

    SDL_SetWindowTitle(g.window, "Dogs Gone Wild");
    return g;
}

void destroyGraphics(Graphics* g)
{
    SDL_DestroyWindow(g->window);
    return;
}