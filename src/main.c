#include "game.h"
#include "hashtable.h"

#define WIDTH 720
#define HEIGHT 480

static void deleteItem(void* i);

int main(int argc, char* arv[])
{
    Game game = initializeGame(WIDTH, HEIGHT);
    destroyGame(&game);

	// printf("Currently testing Hash Table functionality within %s\n", __FILE__);
	// HashTable ht = initializeHashTable(50, &deleteItem);
	// deleteHashTable(&ht);
    return 0;
}

static void deleteItem(void* i) {
    if(i == NULL)
        return;

    // Cast void* and delete
    return;
}