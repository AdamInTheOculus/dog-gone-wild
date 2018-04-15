
#include "game.h"
#include "HashTableAPI.h"
#include "debug.h"
#include <time.h>

#define WIDTH 720
#define HEIGHT 480

int main(int argc, char* arv[])
{
    Game game = initializeGame(WIDTH, HEIGHT);
    runGame(&game);
    destroyGame(&game);
    return 0;
}
