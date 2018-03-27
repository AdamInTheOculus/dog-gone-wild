
# Specify compiler, flags, and file directories
CC = gcc
C_FLAGS = -Wall -std=c11 -g
BIN = bin
SRC = src/graphics.c src/game.c src/main.c

# Cross platform include/library locations
INCLUDES = -Iinclude -I/usr/local/include
LINKS = -L/usr/local/lib

# Additional libs to include
SDL_LIBS = -lSDL2

game:
	$(CC) $(C_FLAGS) $(INCLUDES) $(LINKS) $(SRC) $(SDL_LIBS) -o $(BIN)/main

clean:
	rm -r bin/*