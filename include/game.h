#ifndef GAME_H
#define GAME_H

#include "animatedsprite.h"
#include "graphics.h"
#include "input.h"

#define FPS 60
#define MAX_FRAME_TIME (FPS * 100) / FPS
#define MIN(a, b) (((a) > (b)) ? (b) : (a))

typedef struct Game {

    int width;
    int height;
    Graphics graphics;
    Input input;
    AnimatedSprite player;
    
} Game;

Game initializeGame();
void destroyGame(Game* game);
void runGame(Game* game);
void loopGame(Game* game, Input* input, Graphics* graphics);
void updateGame(Game* game, Input* input, float elapsedTime);
void drawGame(Game* game, Graphics* graphics);

#endif