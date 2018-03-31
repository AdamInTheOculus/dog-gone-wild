
# Specify compiler
CC = gcc

# Specify compiler flags
# Different OS use different flags
C_FLAGS = -Wall -g

# Don't include C11 standard on Windows (todo: figure out why?)
ifneq ($(OS), Windows_NT)
	C_FLAGS += -std=c11
endif

BIN = bin

# Cross platform include/library locations
INCLUDES = -Iinclude
ifneq ($(OS), Windows_NT)
	SRC = src\graphics. src\game.c src\main.c
	
	SDL_LIBS = -lSDL2
	SDL_CFLAGS := $(shell sdl2-config --cflags)
	SDL_LDFLAGS := $(shell sdl2-config --libs)
else

#--------------------------------#
#--  Additional Windows flags  --#
#--------------------------------#
	# -w suppresses warnings
	# -W1,-subsystem,windows gets rid of console window 
	COMPILER_FLAGS = -w -Wl,-subsystem,windows
	SRC = src/graphics.c src/game.c src/main.c
	SDL_CFLAGS = -IC:\mingw32-dev\include
	SDL_LDFLAGS = -LC:\mingw32-dev\lib
	SDL_LIBS = -lmingw32 -lSDL2main -lSDL2
endif

ifeq ($(OS), Windows_NT)
all:
	$(CC) $(C_FLAGS) $(SRC) $(INCLUDES) $(SDL_CFLAGS) $(SDL_LDFLAGS) $(COMPILER_FLAGS) $(SDL_LIBS) -o $(BIN)\main
	
clean:
	rm -r bin\*
else
all:
	$(CC) $(C_FLAGS) $(SRC) $(INCLUDES) $(SDL_CFLAGS) $(SDL_LDFLAGS) $(SDL_LIBS) -o $(BIN)/main
	
clean:
	rm -r bin/*
endif
