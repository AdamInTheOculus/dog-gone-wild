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

    // Set animation to idle position
    strcpy(as->currentAnimation, "walkRight");
    strcpy(as->lastAnimation, "");
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

    if(SDL_Init(SDL_INIT_EVERYTHING)) {
        log_error_exit("Failed to initialize SDL. %s\n", SDL_GetError());
    }

    Game game;
    game.width = width;
    game.height = height;
    game.graphics = initializeGraphics(game.width, game.height);
    game.input = initializeInput();
    game.player = createAnimatedSprite(
        &game.graphics,
        "assets/sprites/ff6-sabin.png",
        4,             // # of animations a sprite has
        3,62,          // Location in spritesheet
        16,24,         // Size
        100,100,       // Position in game
        100,              // Time to update (in ms)
        &updateSprite,
        &deleteSprite,
        &setupAnimations,
        &animationDone
    );

    return game;
}

void destroyGame(Game* game)
{
    if(game == NULL) {
        log_error_exit("Game pointer is NULL. %s\n", SDL_GetError());
    }

    printf("Destroying game ... was exit requested? [%d]\n", game->input.exitRequested);

    destroyInput(&game->input);
    destroyGraphics(&game->graphics);
    SDL_Quit();
}

void runGame(Game* game)
{
    loopGame(game, &game->input, &game->graphics);
}

void loopGame(Game* game, Input* input, Graphics* graphics)
{
    if(input == NULL) {
        log_error_exit("Input is NULL. %s\n", SDL_GetError());
    }

    // ===================================================
    // == Initialize animations before game loop starts ==
    // ===================================================
    game->player.setupAnimations(&game->player);

    // Keep track of time
    double currentTime = SDL_GetTicks();

    while(true)
    {
        double newTime = SDL_GetTicks();
        double deltaTime = newTime - currentTime;
        if(deltaTime < 13) {
            continue;
        }

        printf("Delta time: %.2f\n", deltaTime);
        currentTime = newTime;

        // TODO: Safe shutdown when user wants to exit
        if(wasKeyPressed(input, SDL_SCANCODE_ESCAPE) || wasExitRequested(input)) {
            return;
        }

        else if(isKeyHeld(input, SDL_SCANCODE_S) && isKeyHeld(input, SDL_SCANCODE_D)) {
            game->player.facingLeft = false;
            playAnimation(&game->player, "crouchRight", false);
        }

        else if(isKeyHeld(input, SDL_SCANCODE_S) && isKeyHeld(input, SDL_SCANCODE_A)) {
            game->player.facingLeft = true;
            playAnimation(&game->player, "crouchLeft", false);
        }

        else if(isKeyHeld(input, SDL_SCANCODE_D)) {
            game->player.facingLeft = false;
            playAnimation(&game->player, "walkRight", false);
        }

        else if(isKeyHeld(input, SDL_SCANCODE_A)) {
            game->player.facingLeft = true;
            playAnimation(&game->player, "walkLeft", false);
        }

        else if(isKeyHeld(input, SDL_SCANCODE_S)) {
            if(game->player.facingLeft)
                playAnimation(&game->player, "crouchLeft", false);
            else
                playAnimation(&game->player, "crouchRight", false);
        }

        // TODO: Create idle animation
        else {
            if(game->player.facingLeft)
                playAnimation(&game->player, "walkLeft", false);
            else
                playAnimation(&game->player, "walkRight", false);
        }

        updateGame(game, input, MIN(deltaTime, MAX_FRAME_TIME));
        drawGame(game, graphics);
    }
}

void updateGame(Game* game, Input* input, float elapsedTime)
{
    if(game == NULL) {
        log_error_exit("Game pointer is NULL. %s\n", SDL_GetError());
    }

    updateInput(input);
    updateAnimatedSprite(&game->player, elapsedTime);
    return;
}

void drawGame(Game* game, Graphics* graphics)
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
