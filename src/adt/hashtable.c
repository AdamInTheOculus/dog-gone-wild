/**
 * @file hashtable.c
 * @author Adam Sinclair
 * @created Sun April 8 2018
 * @purpose Implementation of HashTable
**/

#include "hashtable.h"

int main(int argc, char* argv[])
{
    char* a = "block1.png";
    char* b = "block2.png";
    char* c = "block3.png";
    char* d = "water1.png";
    char* e = "water2.png";
    char* f = "water3.png";
    char* g = "smile.png";
    char* h = "sad.png";
    char* i = "wave1.mp3";
    char* j = "wave2.mp3";
    char* k = "wave3.mp3";
    char* l = "punch1.mp3";
    char* m = "punch2.mp3";
    char* n = "kick1.mp3";
    char* o = "kick2.mp3";
    char* p = "bark.mp3";
    char* q = "whine.mp3";
    char* r = "laugh1.mp3";
    char* s = "laugh2.mp3";
    char* t = "laugh3.mp3";
    char* u = "cry1.mp3";
    char* v = "cry2.mp3";
    char* w = "music1.mp3";
    char* x = "music2.mp3";
    char* y = "theme.mp3";
    char* z = "credits.mp3";

    int size = 30;

    printf("Value: %d\n", hash(a, size));
    printf("Value: %d\n", hash(b, size));
    printf("Value: %d\n", hash(c, size));
    printf("Value: %d\n", hash(d, size));
    printf("Value: %d\n", hash(e, size));
    printf("Value: %d\n", hash(f, size));
    printf("Value: %d\n", hash(g, size));
    printf("Value: %d\n", hash(h, size));
    printf("---------------\n");
    printf("Value: %d\n", hash(i, size));
    printf("Value: %d\n", hash(j, size));
    printf("Value: %d\n", hash(k, size));
    printf("Value: %d\n", hash(l, size));
    printf("Value: %d\n", hash(m, size));
    printf("Value: %d\n", hash(n, size));
    printf("Value: %d\n", hash(o, size));
    printf("Value: %d\n", hash(p, size));
    printf("Value: %d\n", hash(q, size));
    printf("Value: %d\n", hash(r, size));
    printf("Value: %d\n", hash(s, size));
    printf("Value: %d\n", hash(t, size));
    printf("Value: %d\n", hash(u, size));
    printf("Value: %d\n", hash(v, size));
    printf("Value: %d\n", hash(w, size));
    printf("Value: %d\n", hash(x, size));
    printf("Value: %d\n", hash(y, size));
    printf("Value: %d\n", hash(z, size));

    return 0;
}

/**
 * @purpose Statically creates new HashTable struct. 
 *          Each individual node is dynamically allocated.
 *
**/
HashTable initializeHashTable(int size, void (*deleteFunction)(void* data))
{
    if(size < 1)
        log_error_exit("Size parameter is invalid: [%d]", size);
    if(deleteFunction == NULL)
        log_error_exit("HashTable with size [%d] has NULL function pointer.", size);

    HashTable ht;
    ht.size = size;
    ht.deleteData = deleteFunction;

    if((ht.items = calloc((size_t)ht.size, sizeof(HashItem*))) == NULL)
        log_error_exit("Initializing hash table of size [%d] failed due to malloc error.", size);

    return ht;
}

void deleteHashTable(HashTable* table)
{
    if(table == NULL)
        return;

    for(int i=0; i<table->size; i++)
    {
        HashItem* item = NULL;
        item = table->items[i];

        if(item != NULL)
            table->deleteData(item);
    }

    free(table->items);
}

/** 
 * Implement FNV-1a hash algorithm
 * https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
 *
 * @param string Represents a label for some information. 
 * @return A non-zero number representing the index in a table.
**/
unsigned int hash(char* string, unsigned int size)
{
    if(string == NULL || strlen(string) < 1)
        return 0;

    int len = strlen(string);
    unsigned long hash = 2166136261u;

    for(int i=0; i<len; i++)
    {
        hash ^= string[i];
        hash *= 16777619u;
    }

    return hash % size;
}