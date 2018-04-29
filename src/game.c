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

void setupAnimations(AnimatedSprite* as)
{
    int frameCount = 4;

    Vector2 left_location = {0, 60};
    Vector2 left_size =     {20,24};
    Vector2 left_offset =   {0, 0};
    addAnimation(as, "walkLeft", frameCount, left_location, left_size, left_offset);

    Vector2 right_location = {0, 90};
    Vector2 right_size = left_size;
    Vector2 right_offset = left_offset;
    addAnimation(as, "walkRight", frameCount, right_location, right_size, right_offset);

    Vector2 crouch_left_location = {110, 140};
    Vector2 crouch_left_size = {20, 20};
    Vector2 crouch_left_offset = {0, 0};
    addAnimation(as, "crouchLeft", 1, crouch_left_location, crouch_left_size, crouch_left_offset);

    Vector2 crouch_right_location = {110, 120};
    Vector2 crouch_right_size = {20, 20};
    Vector2 crouch_right_offset = {0, 0};
    addAnimation(as, "crouchRight", 1, crouch_right_location, crouch_right_size, crouch_right_offset);

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
        4,             // # of animations a sprite has
        3,62,          // Location in spritesheet
        16,24,         // Size
        100,100,       // Position in game
        8000,            // timeToUpdate
        &updateSprite,
        &deleteSprite,
        &setupAnimations,
        &animationDone
    );

    log_debug("AnimatedSprite at address: [%p]\n", &game->player);
    game->player.setupAnimations(&game->player);
    playAnimation(&game->player, "walkRight", false);
    log_debug("Playing animation: [%s]\n", game->player.currentAnimation);

    // Start of game loop
    int LAST_UPDATE_TIME = SDL_GetTicks();
    while(true)
    {
        clearInput(input);
        updateInput(input);

        // TODO: Safe shutdown when user wants to exit
        if(wasKeyPressed(input, SDL_SCANCODE_ESCAPE) || wasExitRequested(input))
            return;

        if(wasKeyPressed(input, SDL_SCANCODE_S) && wasKeyPressed(input, SDL_SCANCODE_A))
            playAnimation(&game->player, "crouchLeft", false);

        if(wasKeyPressed(input, SDL_SCANCODE_D))
            playAnimation(&game->player, "walkRight", false);

        if(wasKeyPressed(input, SDL_SCANCODE_A))
            playAnimation(&game->player, "walkLeft", false);

        if(wasKeyPressed(input, SDL_SCANCODE_S))
            playAnimation(&game->player, "crouchRight", false);

        if(wasKeyReleased(input, SDL_SCANCODE_S))
            playAnimation(&game->player, "walkRight", false);
        

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
