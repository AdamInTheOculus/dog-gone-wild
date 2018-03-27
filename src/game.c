/**
 * @file game.c
 * @author Adam Sinclair
 * @created Tues March 27 2018
 * @purpose Entry point for Dog Gone Wild
**/

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 720
#define SCREEN_HEIGHT 480

int main(int argc, char* arv[])
{
    // Window that will be rendered to
    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;

    // Attempt to initialize SDL
    if(SDL_Init( SDL_INIT_VIDEO ) < 0)
    {
        fprintf(stderr, "ERROR: SDL could not initialize!\n\tFile [%s] at line [%d]\n\t%s\n", __FILE__, __LINE__ - 1, SDL_GetError());
        return -1;
    }

    // Create application window with following specifications
    // @annotate https://wiki.libsdl.org/SDL_CreateWindow
    window = SDL_CreateWindow (
        "Dog Gone Wild",            // Game title
        SDL_WINDOWPOS_UNDEFINED,    //  
        SDL_WINDOWPOS_UNDEFINED,    //
        SCREEN_WIDTH,               // Width of window
        SCREEN_HEIGHT,              // Height of window
        SDL_WINDOW_SHOWN            // Show window when started
    );

    // Ensure window was created successfully
    if(window == NULL)
    {
        fprintf(stderr, "ERROR: Could not create SDL window!\n\tFile [%s] at line [%d]\n\t%s\n", __FILE__, __LINE__ - 1, SDL_GetError());
        return -1;
    }

    screenSurface = SDL_GetWindowSurface(window);

    // Fill screen with black
    // @annotate https://wiki.libsdl.org/SDL_FillRect
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));

    // Update window surface
    SDL_UpdateWindowSurface(window);

    // Loop until user clicks EXIT or presses ESCAPE
    bool isRunning = true;
    while(isRunning)
    {
        SDL_Event e;
        while(SDL_PollEvent(&e))
        {
            switch(e.type)
            {
                case SDL_QUIT:
                    isRunning = false;
                    break;

                case SDL_KEYUP:
                    if(e.key.keysym.sym == SDLK_ESCAPE)
                    {
                        isRunning = false;
                        break;
                    }

                default: ;

            }
        }
    }

    // Clean up
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
