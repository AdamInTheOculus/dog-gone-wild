#ifndef GAME_H
#define GAME_H

#include "graphics.h"
#include "input.h"

typedef struct Game {

    int width;
    int height;
    
} Game;

Game initializeGame();
void destroyGame(Game* game);
void loop(Input* input);
void draw(Graphics* g);
void update(float elapsedTime);

#endif