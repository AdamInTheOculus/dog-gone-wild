#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <SDL2/SDL.h>

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
    SDL_Window* window;
    SDL_Renderer* renderer;
    int width;
    int height;
} Graphics;

Graphics initializeGraphics(const int width, const int height);
void deleteGraphics(Graphics* g);

#endif