#include "game.h"

#define WIDTH 720
#define HEIGHT 380

int main(int argc, char* arv[])
{
    Game game = initializeGame(WIDTH, HEIGHT);
    printf("Address of Game: %p\n", &game);
    gameLoop(&game);
    destroyGame(&game);

    return 0;
}