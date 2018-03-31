/**
 * @file game.c
 * @author Adam Sinclair
 * @created Tues March 27 2018
 * @purpose Entry point for Dog Gone Wild
**/

#include "game.h"

Game initializeGame(const int width, const int height)
{
    Game game;
    game.width = width;
    game.height = height;

    printf("Windows test!\n");

    if(SDL_Init(SDL_INIT_EVERYTHING))
    {
        log_error("Failed to initialize SDL. %s\n", SDL_GetError());
        exit(-1);
    }

    return game;
}

void destroyGame(Game* game)
{
    if(game == NULL)
        return;
}

void gameLoop(Game* game)
{
    if(game == NULL)
    {
        log_error("Game pointer is NULL. %s\n", SDL_GetError());
        return;
    }

    Graphics g = initializeGraphics(game->width, game->height);
    SDL_Event e;

    while(true)
    {
        if(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
                return;

            else if(e.type == SDL_KEYUP)
            {
                switch(e.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        return; break;
                }
            }
        }
    }
}

void draw(Graphics* g)
{
    if(g == NULL)
    {
        log_error("Graphics pointer is NULL. %s\n", SDL_GetError());
        return;
    }
}

void update(float elapsedTime)
{
    return;
}
