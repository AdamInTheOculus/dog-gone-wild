#include "animatedsprite.h"
#include "debug.h"

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
){
    // ====================================
    // == Validate all pointer arguments ==
    // ====================================
    if(g == NULL)
        log_error_exit("%s", "Graphics pointer is NULL.\n");
    if(filePath == NULL || strlen(filePath) < 1)
        log_error_exit("%s", "Filepath is NULL or empty.\n");
    if(deleteSprite == NULL)
        log_error_exit("%s", "deleteSprite() is NULL.\n");
    if(updateSprite == NULL)
        log_error_exit("%s", "updateSprite() is NULL.\n");
    if(setupAnimations == NULL)
        log_error_exit("%s", "setupAnimations() is NULL.\n");

    // =================================================
    // == Initialize AnimatedSprite and assign values ==
    // =================================================
    AnimatedSprite as;
    as.sprite = createSprite(
        graphics, filePath, srcX, srcY, width, height,
        posX, posY, deleteSprite, updateSprite
    );

    as.frameIndex = 0;
    as.timeToUpdate = timeToUpdate;
    as.visible = true;
}

/**
 * Plays animation provided by char* if not already playing.
**/
void playAnimation(char* animation, bool playOnce)
{

}

/**
 * Updates the animated sprite (timer).
**/
void updateAnimatedSprite(int elapsedTime)
{

}

/**
 * Draws animated sprite to screen.
**/
void drawAnimatedSprite(Graphics* g, int posX, int posY)
{

}