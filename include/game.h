#ifndef GAME_H
#define GAME_H

#include "sprite.h"
#include "graphics.h"
#include "input.h"

#define FPS 50
#define MAX_FRAME_TIME (5 * 1000) / FPS
#define MIN(a, b) (((a) > (b)) ? (b) : (a))

typedef struct Game {

    int width;
    int height;
    Graphics graphics;
    Input input;
    Sprite player;
    
} Game;

Game initializeGame();
void destroyGame(Game* game);
void runGame(Game* game);
void loop(Game* game, Input* input, Graphics* graphics);
void draw(Game* game , Graphics* graphics);
void update(float elapsedTime);

#endif