/**
 * @file game.c
 * @author Adam Sinclair
 * @created Tues March 27 2018
 * @purpose Entry point for Dog Gone Wild
**/

#include "game.h"
#include "debug.h"

void animationDone(char* animation)
{
    return;
}

void setupAnimations(AnimatedSprite* as, const char* name)
{
    int frameCount = 3;

    Vector2 location = {0,0};
    Vector2 size = {16,16};
    Vector2 offset = {0,0};

    addAnimation(
        as,             // AnimatedSprite
        name,           // Name of animation
        frameCount,     // # frames for animation
        location,          // Start position
        size,        // Size of each frame
        offset          // Offset
    );
}

void updateSprite()
{
    return;
}

void deleteSprite()
{
    return;
}

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

    game->player = createAnimatedSprite(
        graphics,
        "assets/sprites/ff6-sabin.png",
        3,             // # of animations a sprite has
        1,60,          // Location in spritesheet
        20,30,         // Size
        100,100,       // Position in game
        50,            // timeToUpdate
        &updateSprite,
        &deleteSprite,
        &setupAnimations,
        &animationDone
    );

    game->player.setupAnimations(&game->player, "runLeft");
    playAnimation(&game->player, "runLeft", false);

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

        update(game, MIN(ELAPSED_TIME_MS, MAX_FRAME_TIME));
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
    Vector2 location = {100, 100};
    drawAnimatedSprite(graphics, &game->player, location);
    renderGraphics(graphics);
}

void update(Game* game, float elapsedTime)
{
    if(game == NULL)
        log_error_exit("Game pointer is NULL. %s\n", SDL_GetError());

    updateAnimatedSprite(&game->player, elapsedTime);

    return;
}
