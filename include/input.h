#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

#define PRESSED_KEY 0
#define RELEASED_KEY 1
#define HELD_KEY 2

typedef struct Input {
    bool (*keycode)[3];
    int size;
    bool exitRequested;
} Input;

Input initializeInput();
void destroyInput(Input* input);

void updateInput(Input* input);
void clearInput(Input* input); 
void keyUpEvent(Input* input, SDL_Event e);
void keyDownEvent(Input* input, SDL_Event e);

bool wasKeyPressed(const Input* input, SDL_Scancode key);
bool wasKeyReleased(const Input* input, SDL_Scancode key);
bool wasExitRequested(const Input* input);
bool isKeyHeld(const Input* input, SDL_Scancode key);

#endif