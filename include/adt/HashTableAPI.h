#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "LinkedListAPI.h"

#define DEBUG 1
#ifdef DEBUG

#define log_error_exit(fmt, ...) {\
            fprintf(stderr, "ERROR ==> %s:%d %s() ==> " fmt, __FILE__, __LINE__, __func__, __VA_ARGS__);\
            exit(-1);\
        }
#endif

typedef struct Entry {
    List chain; /* Handle collisions via chaining */
} Entry;

typedef struct HashTable {
    int size;
    Entry* entries; /* Each entry is a LinkedList */
} HashTable;

HashTable initializeHashTable(int size, char* (*printFunction)(void* toBePrinted), void (*deleteFunction)(void* toBeDeleted), int (*compareFunction)(const void* first, const void* second));
void deleteHashTable(HashTable* table);

#endif