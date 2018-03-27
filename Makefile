
# Specify compiler, flags, and file directories
CC = gcc
C_FLAGS = -Wall -std=c11 -g
BIN = bin
SRC = src

# Cross platform include/library locations
INCLUDES = -I/usr/local/include 
LINKS = -L/usr/local/lib

# Additional libs to include
SDL_LIBS = -lSDL2

game:
	$(CC) $(C_FLAGS) $(INCLUDES) $(LINKS) $(SRC)/game.c $(SDL_LIBS) -o $(BIN)/game

clean:
	rm -r bin/*