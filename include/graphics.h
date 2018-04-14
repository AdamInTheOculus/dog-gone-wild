#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <SDL2/SDL.h>
#include "HashTableAPI.h"

#define DEBUG 1
#ifdef DEBUG

#define log_error_exit(fmt, ...) {\
            fprintf(stderr, "ERROR ==> %s:%d %s() ==> " fmt, __FILE__, __LINE__, __func__, __VA_ARGS__);\
            exit(-1);\
        }

#define log_debug(fmt, ...) { \
            fprintf(stderr, "DEBUG ==> %s:%d %s() ==> " fmt, __FILE__, __LINE__, __func__, __VA_ARGS__);\
        }

#else
#define log_error_exit(str, ...)
#define log_debug(str, ...)
#endif

typedef struct Graphics {
    int width;
    int height;
    SDL_Window* window;
    SDL_Renderer* renderer;
    HashTable ImageManager;
} Graphics;

Graphics initializeGraphics(int width, int height);
void destroyGraphics(Graphics* g);

// ======================
// ==  Image Handling  ==
// ======================

/** SDL_Surface* loadImage
 * @purpose Loads image into spritesheet, if it doesn't already exist.
 * @param `file` Relative path to image file.
 * @return 
**/
SDL_Surface* loadImage(const char* file);

#endif
