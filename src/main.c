#include "game.h"
#include "HashTableAPI.h"

#define WIDTH 720
#define HEIGHT 480

int main(int argc, char* arv[])
{
    Game game = initializeGame(WIDTH, HEIGHT);
    runGame(&game);
    destroyGame(&game);

	// printf("Currently testing Hash Table functionality within %s\n", __FILE__);
	// HashTable ht = initializeHashTable(50, &deleteItem);
	// deleteHashTable(&ht);
    return 0;
}