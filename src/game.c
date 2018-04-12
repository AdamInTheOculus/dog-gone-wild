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

    int LAST_UPDATE_TIME = SDL_GetTicks();

    // Start of game loop
    while(true)
    {
        clearInput(input);
        updateInput(input);

        // Quit application if ESCAPE key or X is pressed
        if(wasKeyPressed(input, SDL_SCANCODE_ESCAPE) || wasExitRequested(input))
            return;

        // Calculate frame length
        int CURRENT_TIME_MS = SDL_GetTicks();
        int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;

        update(MIN(ELAPSED_TIME_MS, MAX_FRAME_TIME));
        LAST_UPDATE_TIME = ELAPSED_TIME_MS;
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
