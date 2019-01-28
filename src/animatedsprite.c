#include "animatedsprite.h"
#include "debug.h"

/**
 * Local functions required for LinkedList implementation of SDL_Rects.
 * Each node represents an SDL_Rect.
 * Each SDL_Rect represents the position of a sprite within a spritesheet.
**/
static char* printRect(void* toBePrinted);
static void deleteRect(void* toBeDeleted);
static int compareRects(const void* first, const void* second);

/**
 * Local functions required for HashTable implementation of Vector2 offsets.
 * Each node represents a Vector2 struct; see globals.h
 * Each Vector2 represents a set of data in 2 dimensions (x,y).
**/
static char* printVector2(void* toBePrinted);
static void deleteVector2(void* toBeDeleted);
static int compareVector2(const void* first, const void* second);

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
    void (*doneAnimation)(char* animation) // Logic that happens after animation is complete.
){
    // ====================================
    // == Validate all pointer arguments ==
    // ====================================
    if(graphics == NULL)
        log_error_exit("%s", "Graphics pointer is NULL.\n");
    if(filePath == NULL || strlen(filePath) < 1)
        log_error_exit("%s", "Filepath is NULL or empty.\n");
    if(deleteSprite == NULL)
        log_error_exit("%s", "deleteSprite() is NULL.\n");
    if(updateSprite == NULL)
        log_error_exit("%s", "updateSprite() is NULL.\n");
    if(setupAnimations == NULL)
        log_error_exit("%s", "setupAnimations() is NULL.\n");
    if(doneAnimation == NULL)
        log_error_exit("%s", "doneAnimation() is NULL.\n");

    // =========================================================
    // == Initialize AnimatedSprite and assign default values ==
    // =========================================================
    AnimatedSprite as;
    as.sprite = createSprite(
        graphics,
        filePath,
        srcX, srcY,
        width, height,
        posX, posY,
        deleteSprite,
        updateSprite
    );

    as.facingLeft = false;
    as.visible = true;
    as.frameIndex = 0;
    as.timeToUpdate = timeToUpdate;
    as.currentAnimationOnce = false;
    as.currentAnimation[0] = '\0';

    // =======================================================
    // == Initialize HashTables for animations and offsets  ==
    // =======================================================
    as.animations = initializeHashTable(animationCount, &printRect, &deleteRect, &compareRects);
    as.offsets = initializeHashTable(animationCount, &printVector2, &deleteVector2, &compareVector2);

    // ==============================
    // == Assign function pointers ==
    // ==============================
    as.setupAnimations = setupAnimations;
    as.doneAnimation = doneAnimation;

    return as;
}

/**
 * Adds animation and offset to HashTables of a sprite.
**/
void addAnimation(AnimatedSprite* sprite, const char* name, int frameCount, Vector2 position, Vector2 size, Vector2 offset)
{
    if(sprite == NULL)
        log_error_exit("%s", "AnimatedSprite pointer is NULL.\n");
    if(name == NULL || strlen(name) < 1)
        log_error_exit("Name is NULL or has no characters [%s].\n", name);
    if(frameCount < 1)
        log_error_exit("Frame count must be a positive integer. Currently [%d].\n", frameCount);

    // ==========================================
    // == Generate a dynamic list of SDL_Rects ==
    // ==========================================
    List* rectangles = initializeList(&printRect, &deleteRect, &compareRects);
    for (int i=0; i<frameCount; i++)
    {
        // SDL_Rect represents the location of a sprite (x,y) on a spritesheet (2D image).
        SDL_Rect* newRect = NULL;
        if((newRect = malloc(sizeof(SDL_Rect))) == NULL) {
            log_error_exit("Failed to dynamically allocate SDL_Rect for [%s] animation.\n", name);
        }


        newRect->x = size.x * i + position.x;
        newRect->y = position.y;
        newRect->w = size.x;
        newRect->h = size.y;
        insertBack(rectangles, (void*)newRect, name);
    }

    // ============================================
    // == Attempt to insert animation rectangles ==
    // ============================================
    if(insertEntry(&sprite->animations, name, rectangles) == false) {
        log_error_exit("Failed to insert animation [%s] of %d frames.\n", name, frameCount);
    }

    // ========================================
    // == Attempt to insert animation offset ==
    // ========================================
    Vector2* _offset = malloc(sizeof(Vector2));
    _offset->x = offset.x;
    _offset->y = offset.y;

    if(insertEntry(&sprite->offsets, name, (void*)_offset) == false) {
        log_error_exit("Failed to insert offset of animation [%s].\n", name);
    }

    log_debug("Added animation [%s] to animated sprite [%p].\n", name, sprite);
}

/**
 * Resets all animations associated with this sprite.
**/
void resetAnimations(AnimatedSprite* sprite)
{
    if(sprite == NULL) {
        log_error_exit("%s", "AnimatedSprite pointer is NULL.\n");
    }

    clearHashTable(&sprite->animations);
    clearHashTable(&sprite->offsets);
}

/**
 * Plays animation given by string, if not already playing.
**/
void playAnimation(AnimatedSprite* sprite, char* animation, bool playOnce)
{
    if(sprite == NULL) 
        log_error_exit("%s", "AnimatedSprite pointer is NULL.\n");
    if(animation == NULL || strlen(animation) < 1)
        log_error_exit("%s", "Animation string is either NULL or empty.\n");

    sprite->currentAnimationOnce = playOnce;
    if(strcmp(sprite->currentAnimation, animation) != 0) {
        strcpy(sprite->currentAnimation, animation);
        sprite->frameIndex = 0;
    }
}

/**
 * Stops the current animation playing.
**/
void stopAnimation(AnimatedSprite* sprite)
{
    if(sprite == NULL) {
        log_error_exit("%s", "AnimatedSprite pointer is NULL.\n");
    }

    sprite->frameIndex = 0;
    sprite->doneAnimation(sprite->currentAnimation);
}

/**
 * Changes the visibility of an animated sprite.
**/
void setAnimationVisible(AnimatedSprite* sprite, bool visibility)
{
    if(sprite == NULL) {
        log_error_exit("%s", "AnimatedSprite pointer is NULL.\n");
    }

    sprite->visible = visibility;
}

/**
 * Updates the animated sprite (timer).
**/
void updateAnimatedSprite(AnimatedSprite* sprite, int elapsedTime)
{
    if(sprite == NULL) {
        log_error_exit("%s", "AnimatedSprite pointer is NULL.\n");
    }

    // ===========================
    // == Update last animation ==
    // ===========================
    strcpy(sprite->lastAnimation, sprite->currentAnimation);

    // ========================================
    // == Update Sprite and time that passed ==
    // ========================================
    sprite->sprite.update(&sprite->sprite);
    sprite->timeElapsed += elapsedTime;

    if(sprite->timeElapsed >= sprite->timeToUpdate)
    {
        sprite->timeElapsed -= sprite->timeToUpdate;

        void* animations = NULL;
        if((animations = getEntry(&sprite->animations, sprite->currentAnimation)) == NULL) {
            log_error_exit("Failed to get animations for [%s].\n", sprite->currentAnimation);
        }

        List* animList = (List*)animations;

        // ==============================================================
        // == Check if there are more images to animate for our sprite ==
        // ==============================================================
        if(sprite->frameIndex < getLength(*animList) - 1)
            sprite->frameIndex++;

        // ========================================
        // == If not, start animation over again ==
        // ========================================
        else
        {
            if(sprite->currentAnimationOnce) {
                setAnimationVisible(sprite, false);
            }

            sprite->frameIndex = 0;
            sprite->doneAnimation(sprite->currentAnimation);
        }
    }
}

/**
 * Draws animated sprite to screen.
**/
void drawAnimatedSprite(Graphics* g, AnimatedSprite* sprite, Vector2 pos)
{
    if(g == NULL) {
        log_error_exit("%s", "Graphics pointer is NULL.\n");
    } else if(sprite == NULL) {
        log_error_exit("%s", "AnimatedSprite pointer is NULL.\n");
    }


    if(sprite->visible == false) {
        return;
    }

    // // Retrieve offset Vector2 from table
    // void* offsetPtr = getEntry(&sprite->offsets, sprite->currentAnimation);
    // Vector2* offset = (Vector2*)offsetPtr;

    // 
    SDL_Rect destRect;
    destRect.x = pos.x;
    destRect.y = pos.y;
    destRect.w = sprite->sprite.srcRect.w * SPRITE_SCALE;
    destRect.h = sprite->sprite.srcRect.h * SPRITE_SCALE;

    SDL_Rect* srcRect = getAnimationAtIndex(sprite);

    blitSurface(g, sprite->sprite.spriteSheet, srcRect, &destRect);
}

/**
 * Returns pointer to SDL_Rect of animation at current index of AnimatedSprite*
**/
SDL_Rect* getAnimationAtIndex(AnimatedSprite* sprite)
{
    if(sprite == NULL) {
        log_error_exit("%s", "AnimatedSprite pointer is NULL.\n");
    }

    // Get animation list from HashTable
    void* entry = getEntry(&sprite->animations, sprite->currentAnimation);
    List* animations = (List*)entry;

    // Reminder: `animations` is a LinkedList
    // Iterate through list until SDL_Rect is found
    int counter = 0;
    ListIterator iter = createIterator(animations);
    void* element = NULL;
    while((element = nextElement(&iter)) != NULL)
    {
        if(counter == sprite->frameIndex) {
            return (SDL_Rect*)element;
        }

        counter++;
    }

    // Return NULL if nothing is found.
    return NULL;
}

// =============================
// ==                         ==
// ==     HELPER FUNTIONS     ==
// ==                         ==
// =============================
/**
 * Local functions required for LinkedList implementation for SDL_Rects.
 * Each node represents an SDL_Rect.
 * Each SDL_Rect represents the position of a sprite within a spritesheet.
**/
static char* printRect(void* toBePrinted)
{ 
    if(toBePrinted == NULL) {
        return NULL;
    }

    SDL_Rect* rect = (SDL_Rect*)toBePrinted;

    int size = 40;
    char* string = NULL;

    if((string = malloc(sizeof(char) * size)) == NULL) {
        log_error_exit("Failed to allocate [%d] bytes.\n", size);
    }

    sprintf(string,
        "SDL_Rect: x=%d, y=%d, w=%d, h=%d\n",
        rect->x, rect->y, rect->w, rect->h
    );

    return string;
}

static int compareRects(const void* first, const void* second)
{
    return 0; 
}

static void deleteRect(void* toBeDeleted)
{
    if(toBeDeleted == NULL) {
        return;
    }

    SDL_Rect* rect = (SDL_Rect*)toBeDeleted;
    free(rect);
    rect = NULL;
}


/**
 * Local functions required for HashTable implementation of Vector2 offsets.
 * Each node represents a Vector2 struct; see globals.h
 * Each Vector2 represents a set of data in 2 dimensions (x,y).
**/
static char* printVector2(void* toBePrinted)
{
    if(toBePrinted == NULL) {
        return NULL;
    }

    // Vector2* vec2 = (Vector2*)toBePrinted;

    int size = 40;
    char* string = NULL;

    if((string = malloc(sizeof(char) * size)) == NULL) {
        log_error_exit("Failed to allocate [%d] bytes.\n", size);
    }

    sprintf(string, "%s ==> printVector2() - Not implemented.\n", __FILE__);
    return string;
}

static void deleteVector2(void* toBeDeleted)
{
    if(toBeDeleted == NULL) {
        return;
    }

    Vector2* vec2 = (Vector2*)toBeDeleted;
    free(vec2);
    vec2 = NULL;
}

static int compareVector2(const void* first, const void* second)
{
    return 0;
}