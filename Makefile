
# Specify compiler
CC = gcc

# Specify compiler flags
# Different OS use different flags
C_FLAGS = -Wall -g

BIN = bin

# Cross platform include/library locations
INCLUDES = -Iinclude -Iinclude/adt
ifneq ($(OS), Windows_NT)
	C_FLAGS += -std=c11
	SRC = src/input.c src/graphics.c src/game.c src/main.c src/sprite.c
	SRC += src/adt/HashTableAPI.c src/adt/LinkedListAPI.c
	SDL_CFLAGS := $(shell sdl2-config --cflags)
	SDL_LDFLAGS := $(shell sdl2-config --libs)
	SDL_LIBS = -lSDL2_image -lSDL2_ttf
else

#--------------------------------#
#--  Additional Windows flags  --#
#--------------------------------#
	# -w suppresses warnings
	# -W1,-subsystem,windows gets rid of console window 
	COMPILER_FLAGS = -w
	SRC = src\input.c src\graphics.c src\game.c src\main.c src\sprite.c
	SRC += src\adt\HashTableAPI.c src\adt\LinkedListAPI.c
	SDL_CFLAGS = -Iwindows\mingw32-dev\include
	SDL_LDFLAGS = -Lwindows\mingw32-dev\lib
	SDL_LIBS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
endif

ifeq ($(OS), Windows_NT)
all:
	$(CC) $(C_FLAGS) $(SRC) $(INCLUDES) $(SDL_CFLAGS) $(SDL_LDFLAGS) $(COMPILER_FLAGS) $(SDL_LIBS) -o $(BIN)\main

hash:
	$(CC) $(C_FLAGS) $(INCLUDES) src\adt\LinkedListAPI.c src\adt\HashTableAPI.c src\test\hashtest.c -o $(BIN)\hash
	
clean:
	del bin\main.exe bin\hash.exe
else
all:
	clear
	$(CC) $(C_FLAGS) $(SRC) $(INCLUDES) $(SDL_CFLAGS) $(SDL_LDFLAGS) $(SDL_LIBS) -o $(BIN)/main
	
# Optional rule for testing HashTable
# Ensure hashtable.c has an `int main()` function
hash:
	$(CC) $(C_FLAGS) $(INCLUDES) src/adt/* src/test/hashtest.c -o $(BIN)/hash

clean:
	rm -r bin/*
endif
