
# Specify compiler
CC = gcc

# Specify C flags
C_FLAGS = -Wall -std=c11 -g
INCLUDES = -I/usr/local/include 
LINKS = -L/usr/local/lib
SDL_LIBS = -lSDL2
BIN = bin
SRC = src

game:
	$(CC) $(C_FLAGS) $(INCLUDES) $(LINKS) $(SRC)/game.c $(SDL_LIBS) -o $(BIN)/game

clean:
	rm -r bin/*