
#include "game.h"
#include "HashTableAPI.h"
#include "debug.h"

#define WIDTH 720
#define HEIGHT 480

typedef struct File {
    char path[50];
    int size;
} File;

char* printFile(void* toBePrinted);
void deleteFile(void* toBeDeleted);
int compareFiles(const void* first, const void* second);

File* createFile(const char* path, int size);

int main(int argc, char* arv[])
{
    // Game game = initializeGame(WIDTH, HEIGHT);
    // runGame(&game);
    // destroyGame(&game);

	log("%s", "Currently testing Hash Table functionality.");
	HashTable textureManager = initializeHashTable(50, &printFile, &deleteFile, &compareFiles);

    File* f1 = createFile("hello.mp3", 500);
    File* f2 = createFile("oh_hey.mp3", 250);
    File* f3 = createFile("stopit.mp3", 700);
    File* f4 = createFile("hello1.mp3", 500);
    File* f5 = createFile("oh_hey1.mp3", 250);
    File* f6 = createFile("stopit1.mp3", 700);
    File* f7 = createFile("hello2.mp3", 500);
    File* f8 = createFile("oh_hey2.mp3", 250);
    File* f9 = createFile("stopit2.mp3", 700);
    File* f10 = createFile("hello3.mp3", 500);
    File* f11 = createFile("oh_hey3.mp3", 250);
    File* f12 = createFile("stopit3.mp3", 700);

    insertEntry(&textureManager, f1->path, f1);
    insertEntry(&textureManager, f2->path, f2);
    insertEntry(&textureManager, f3->path, f3);
    insertEntry(&textureManager, f4->path, f4);
    insertEntry(&textureManager, f5->path, f5);
    insertEntry(&textureManager, f6->path, f6);
    insertEntry(&textureManager, f7->path, f7);
    insertEntry(&textureManager, f8->path, f8);
    insertEntry(&textureManager, f9->path, f9);
    insertEntry(&textureManager, f10->path, f10);
    insertEntry(&textureManager, f11->path, f11);
    insertEntry(&textureManager, f12->path, f12);

	deleteHashTable(&textureManager);
    return 0;
}

File* createFile(const char* path, int size)
{
    File* f = malloc(sizeof(File));
    strcpy(f->path, path);
    f->size = size;
    return f;
}

void deleteFile(void* toBeDeleted)
{
    File* file = (File*)toBeDeleted;
    free(file);
}

char* printFile(void* toBePrinted)
{
    File* file = (File*)toBePrinted;

    char* string = malloc(sizeof(char) * 100);
    sprintf(string, 
        "File Path: %s, Size: %d\n", 
        file->path, file->size 
    );

    return string;
}

int compareFiles(const void* first, const void* second)
{
    File* a = (File*)first;
    File* b = (File*)second;

    int result = strcmp(a->path, b->path);
    if(result == 0)
    {
        if(a->size == b->size)
            return 0;
        else if(a->size > b->size)
            return -1;
        else
            return 1;
    }

    return result;
}

