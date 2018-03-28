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

    if(SDL_Init(SDL_INIT_EVERYTHING))
        log_error_exit("Failed to initialize SDL. %s\n", SDL_GetError());

    return game;
}

void destroyGame(Game* game)
{
    if(game == NULL)
        log_error_exit("Game pointer is NULL. %s\n", SDL_GetError());
}

void loop(Game* game)
{
    if(game == NULL)
        log_error_exit("Game pointer is NULL. %s\n", SDL_GetError());

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
        log_error_exit("Graphics pointer is NULL. %s\n", SDL_GetError());
}

void update(float elapsedTime)
{
    return;
}