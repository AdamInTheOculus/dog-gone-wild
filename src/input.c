/**
 * @file input.c
 * @author Adam Sinclair
 * @created Thurs March 29 2018
 * @purpose Contains definitions of Input manager functions
**/

#include "input.h"
#include "debug.h"

#define KEY_COUNT 50
#define KEY_STATE_COUNT 3

Input initializeInput()
{
    Input i;
    i.keycode = malloc(sizeof(bool*) * KEY_COUNT);
    i.size = KEY_COUNT;
    i.exitRequested = false;
    clearInput(&i);
    return i;
}

void destroyInput(Input* input)
{
    if(input == NULL)
        log_error_exit("`input` pointer [%p] is NULL.\n", input);

    free(input->keycode);
    input->keycode = NULL;
    return;
}

void updateInput(Input* input)
{

    clearInput(input);

    SDL_Event e;
    if(SDL_PollEvent(&e))
    {
        if(e.type == SDL_QUIT)
            input->exitRequested = true;
        else if(e.type == SDL_KEYUP)
            keyUpEvent(input, e);
        else if(e.type == SDL_KEYDOWN)
            keyDownEvent(input, e);
    }
}

void clearInput(Input* input)
{
    if(input == NULL)
        log_error_exit("`input` pointer [%p] is NULL.\n", input);

    for(int i=0; i<input->size; i++)
        for(int j=0; j<KEY_STATE_COUNT; j++)
            input->keycode[i][j] = false;

    return;
}
 
void keyUpEvent(Input* input, SDL_Event e)
{
    input->keycode[RELEASED_KEY][e.key.keysym.scancode] = true;
    input->keycode[HELD_KEY][e.key.keysym.scancode] = false;
}

void keyDownEvent(Input* input, SDL_Event e)
{
    input->keycode[PRESSED_KEY][e.key.keysym.scancode] = true;
    input->keycode[HELD_KEY][e.key.keysym.scancode] = true;
}

bool wasKeyPressed(const Input* input, SDL_Scancode key)
{
    return input->keycode[PRESSED_KEY][key];
}

bool wasKeyReleased(const Input* input, SDL_Scancode key)
{
    return input->keycode[RELEASED_KEY][key];
}

bool wasExitRequested(const Input* input)
{
    return input->exitRequested;
}

bool isKeyHeld(const Input* input, SDL_Scancode key)
{
    return input->keycode[HELD_KEY][key];
}