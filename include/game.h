#ifndef GAME_H
#define GAME_H

#include "graphics.h"

typedef struct Game {

    int width;
    int height;
    
} Game;

Game initializeGame();
void destroyGame(Game* game);
void loop(Game* game);
void draw(Graphics* g);
void update(float elapsedTime);

#endif