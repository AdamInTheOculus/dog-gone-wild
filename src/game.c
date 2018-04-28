/**
 * @file game.c
 * @author Adam Sinclair
 * @created Tues March 27 2018
 * @purpose Entry point for Dog Gone Wild
**/

#include "game.h"
#include "debug.h"

Game initializeGame(int width, int height)
{
    Game game;
    game.width = width;
    game.height = height;

    if(SDL_Init(SDL_INIT_EVERYTHING))
        log_error_exit("Failed to initialize SDL. %s\n", SDL_GetError());

    game.graphics = initializeGraphics(game.width, game.height);
    game.input = initializeInput();
    return game;
}

void destroyGame(Game* game)
{
    if(game == NULL)
        log_error_exit("Game pointer is NULL. %s\n", SDL_GetError());

    destroyInput(&game->input);
    destroyGraphics(&game->graphics);
    SDL_Quit();
}

void runGame(Game* game)
{
    loop(game, &game->input, &game->graphics);
}

void loop(Game* game, Input* input, Graphics* graphics)
{
    if(input == NULL)
        log_error_exit("Input is NULL. %s\n", SDL_GetError());

    game->player = createSprite(graphics, "assets/sprites/ff6-sabin.png", 1, 60, 20, 30, 100, 100, NULL, NULL);

    // Start of game loop
    int LAST_UPDATE_TIME = SDL_GetTicks();
    while(true)
    {
        clearInput(input);
        updateInput(input);

        // TODO: Safe shutdown when user wants to exit
        if(wasKeyPressed(input, SDL_SCANCODE_ESCAPE) || wasExitRequested(input))
            return;

        // Calculate frame length
        int CURRENT_TIME_MS = SDL_GetTicks();
        int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;

        update(MIN(ELAPSED_TIME_MS, MAX_FRAME_TIME));
        draw(game, graphics);
        LAST_UPDATE_TIME = ELAPSED_TIME_MS;
    }
}

void draw(Game* game, Graphics* graphics)
{
    if(graphics == NULL)
        log_error_exit("Graphics pointer is NULL. %s\n", SDL_GetError());
    if(game == NULL)
        log_error_exit("Game pointer is NULL. %s\n", SDL_GetError());

    clearGraphics(graphics);
    drawSprite(graphics, &game->player, 100, 100);
    renderGraphics(graphics);
}

void update(float elapsedTime)
{
    return;
}
