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

    Sprite sprite;              // Extends from Sprite class
    HashTable animations;       // Each entry is a LinkedList of SDL_Rects
    HashTable offsets;          // Each entry is Vector2
    int frameIndex;             // What frame we're currently at
    double timeElapsed;         // Indicates how far into the animation we are
    double timeToUpdate;        // Indicates how long to render each sprite
    bool visible;               // Indicates if animation is visible.
    bool currentAnimationOnce;  // Current animation will either run once or loop.
    char currentAnimation[50];  // ID of current animation playing.
    char lastAnimation[50];     // ID of last animation played.

    void (*setupAnimations)();
    void (*doneAnimation)(char* animation);
} AnimatedSprite;

AnimatedSprite createAnimatedSprite(
    Graphics* graphics,
    char* filePath,
    int animationCount,
    int srcX, int srcY,
    int width, int height,
    float posX, float posY,
    float timeToUpdate,
    void (*deleteSprite)(Sprite*),
    void (*updateSprite)(Sprite*),
    void (*setupAnimations)(),
    void (*doneAnimation)(char* animation)
);

/**
 * Plays animation given by string, if not already playing.
**/
void playAnimation(
    AnimatedSprite* sprite,
    char* animation,
    bool playOnce
);

/**
 * Adds animation to HashTable of a specific sprite.
**/
void addAnimation(
    AnimatedSprite* sprite,
    const char* name,
    int frameCount,
    Vector2 position,
    Vector2 size,
    Vector2 offset
);

/**
 * Resets all animations associated with this sprite.
**/
void resetAnimations(
    AnimatedSprite* sprite
);

/**
 * Stops the current animation playing.
**/
void stopAnimation();

/**
 * Changes the visibility of an animated sprite.
**/
void setAnimationVisible(AnimatedSprite* sprite, bool visibility);

/**
 * Updates the animated sprite (timer).
**/
void updateAnimatedSprite(AnimatedSprite* sprite, int elapsedTime);

/**
 * Draws animated sprite to screen.
**/
void drawAnimatedSprite(Graphics* g, AnimatedSprite* sprite, Vector2 pos);

/**
 * Returns pointer to SDL_Rect of animation at current index of AnimatedSprite*
**/
SDL_Rect* getAnimationAtIndex(AnimatedSprite* sprite);

#endif