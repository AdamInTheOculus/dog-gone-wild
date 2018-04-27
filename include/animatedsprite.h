#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include <stdbool.h>
#include "sprite.h"
#include "globals.h" 
#include "HashTableAPI.h"

/** 
 * AnimatedSprite class
 * Holds logic for animating sprites
**/

#define ANIMATE_ONCE true
#define ANIMATE_LOOP false

typedef struct AnimatedSprite {

    Sprite sprite;          // Extends from Sprite class
    HashTable animations;   // Each entry is an array of SDL_Rects
    HashTable offsets;      // Each entry is Vector2
    int frameIndex;         // What frame we're currently at
    double timeElapsed;     // Indicates how far into the animation we are
    bool visible;           // Indicates if animation is visible.

    void (*setupAnimations)();
} AnimatedSprite;

AnimatedSprite createAnimatedSprite(
    Graphics* graphics,
    char* filePath,
    int srcX, int srcY,
    int width, int height,
    float posX, float posY,
    float timeToUpdate,
    void (*deleteSprite)(Sprite*),
    void (*updateSprite)(Sprite*),
    void (*setupAnimations)()
);

/**
 * Plays animation provided by char* if not already playing.
**/
void playAnimation(char* animation, bool playOnce);

/**
 * Updates the animated sprite (timer).
 *  
 * @param int elapsedTime Represents last-frame time
**/
void updateAnimatedSprite(int elapsedTime);

/**
 * Draws animated sprite to screen.
**/
void drawAnimatedSprite(Graphics* g, int posX, int posY);

#endif