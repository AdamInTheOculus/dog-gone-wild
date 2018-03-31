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
        log_error_exit("Failed to initialize SDL. %s\n", SDL_GetError());

    Graphics g = initializeGraphics(game.width, game.height);
    Input input = initializeInput();
    loop(&input);

    destroyInput(&input);
    destroyGraphics(&g);
    return game;
}

void destroyGame(Game* game)
{
    if(game == NULL)
        log_error_exit("Game pointer is NULL. %s\n", SDL_GetError());
}

void loop(Input* input)
{
    if(input == NULL)
        log_error_exit("Input is NULL. %s\n", SDL_GetError());

    clearInput(input);

    SDL_Event e;

    while(true)
    {
        if(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
                return;

            else if(e.type == SDL_KEYUP)
                keyUpEvent(input, e);

            else if(e.type == SDL_KEYDOWN)
            {
                if(e.key.repeat == 0)
                    keyDownEvent(input, e);
            }
        }

        if(wasKeyPressed(input, SDL_SCANCODE_ESCAPE))
            return;
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
