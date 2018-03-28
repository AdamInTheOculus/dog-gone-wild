
# Specify compiler, flags, and file directories
CC = gcc
C_FLAGS = -Wall -std=c11 -g
BIN = bin
SRC = src/graphics.c src/game.c src/main.c

# Cross platform include/library locations
INCLUDES = -Iinclude
SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LDFLAGS := $(shell sdl2-config --libs)

# Additional libs to include
SDL_LIBS = -lSDL2

game:
	$(CC) $(C_FLAGS) $(INCLUDES) $(SDL_CFLAGS) $(SDL_LDFLAGS) $(SRC) $(SDL_LIBS) -o $(BIN)/main

clean:
	rm -r bin/*
