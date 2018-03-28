#include "game.h"

#define WIDTH 720
#define HEIGHT 480

int main(int argc, char* arv[])
{
    Game game = initializeGame(WIDTH, HEIGHT);
    loop(&game);
    destroyGame(&game);

    return 0;
}