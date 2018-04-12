#ifndef GAME_H
#define GAME_H

#include "graphics.h"
#include "input.h"

#define FPS 50
#define MAX_FRAME_TIME (5 * 1000) / FPS
#define MIN(a, b) (((a) > (b)) ? (b) : (a))

typedef struct Game {

    int width;
    int height;
    
} Game;

Game initializeGame();
void destroyGame(Game* game);
void loop(Input* input, Graphics* graphics);
void draw(Graphics* g);
void update(float elapsedTime);

#endif