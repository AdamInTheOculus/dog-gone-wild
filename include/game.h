#ifndef GAME_H
#define GAME_H

#include "graphics.h"

typedef struct Game {

    int width;
    int height;
    
} Game;

Game initializeGame();
void destroyGame(Game* game);
void gameLoop(Game* game);
void draw(Graphics* g);
void update(float elapsedTime);

#endif