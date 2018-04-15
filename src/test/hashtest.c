#include "HashTableAPI.h"
#include "debug.h"
#include <time.h>

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
    clock_t t1, t2;

    t1 = clock();

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

    File* g1 = createFile("hello1.mp3", 500);
    File* g2 = createFile("oh_hey1.mp3", 250);
    File* g3 = createFile("stopit1.mp3", 700);
    File* g4 = createFile("hello11.mp3", 500);
    File* g5 = createFile("oh_hey11.mp3", 250);
    File* g6 = createFile("stopit11.mp3", 700);
    File* g7 = createFile("hello21.mp3", 500);
    File* g8 = createFile("oh_hey21.mp3", 250);
    File* g9 = createFile("stopit21.mp3", 700);
    File* g10 = createFile("hello31.mp3", 500);
    File* g11 = createFile("oh_hey31.mp3", 250);
    File* g12 = createFile("stopit31.mp3", 700);

    if(! insertEntry(&textureManager, f1->path, f1))
        deleteFile(f1);
    if(! insertEntry(&textureManager, f2->path, f2))
        deleteFile(f2);
    if(! insertEntry(&textureManager, f3->path, f3))
        deleteFile(f3);
    if(! insertEntry(&textureManager, f4->path, f4))
        deleteFile(f4);
    if(! insertEntry(&textureManager, f5->path, f5))
        deleteFile(f5);
    if(! insertEntry(&textureManager, f6->path, f6))
        deleteFile(f6);
    if(! insertEntry(&textureManager, f7->path, f7))
        deleteFile(f7);
    if(! insertEntry(&textureManager, f8->path, f8))
        deleteFile(f8);
    if(! insertEntry(&textureManager, f9->path, f9))
        deleteFile(f9);
    if(! insertEntry(&textureManager, f10->path, f10))
        deleteFile(f10);
    if(! insertEntry(&textureManager, f11->path, f11))
        deleteFile(f11);
    if(! insertEntry(&textureManager, f12->path, f12))
        deleteFile(f12);

    // Perform same key insertions to guarantee collisions
    if(! insertEntry(&textureManager, g1->path, g1))
        deleteFile(g1);
    if(! insertEntry(&textureManager, g2->path, g2))
        deleteFile(g2);
    if(! insertEntry(&textureManager, g3->path, g3))
        deleteFile(g3);
    if(! insertEntry(&textureManager, g4->path, g4))
        deleteFile(g4);
    if(! insertEntry(&textureManager, g5->path, g5))
        deleteFile(g5);
    if(! insertEntry(&textureManager, g6->path, g6))
        deleteFile(g6);
    if(! insertEntry(&textureManager, g7->path, g7))
        deleteFile(g7);
    if(! insertEntry(&textureManager, g8->path, g8))
        deleteFile(g8);
    if(! insertEntry(&textureManager, g9->path, g9))
        deleteFile(g9);
    if(! insertEntry(&textureManager, g10->path, g10))
        deleteFile(g10);
    if(! insertEntry(&textureManager, g11->path, g11))
        deleteFile(g11);
    if(! insertEntry(&textureManager, g12->path, g12))
        deleteFile(g12);

    deleteEntry(&textureManager, f1->path);
    deleteEntry(&textureManager, f9->path);
    deleteEntry(&textureManager, NULL); // Intentionally give NULL key
    deleteEntry(NULL, NULL);

    char* string = printFile(getEntry(&textureManager, "hello1.mp3"));
    log_debug("%s", string);
    free(string);

    deleteHashTable(&textureManager);

    t2 = clock();

    log_debug("Elapsed time: %.4f seconds.\n", (double)(t2 - t1) / CLOCKS_PER_SEC);
    return 0;
}

File* createFile(const char* path, int size)
{
    if(path == NULL || strlen(path) < 1)
        return NULL;

    File* f = malloc(sizeof(File));
    strcpy(f->path, path);
    f->size = size;
    return f;
}

void deleteFile(void* toBeDeleted)
{
    if(toBeDeleted == NULL)
        return;

    File* file = (File*)toBeDeleted;
    free(file);
}

char* printFile(void* toBePrinted)
{
    if(toBePrinted == NULL)
        return NULL;

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
    if(first == NULL || second == NULL)
    {
        log_debug("%s", "Parameter(s) is NULL.\n");
        return -2;
    }

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