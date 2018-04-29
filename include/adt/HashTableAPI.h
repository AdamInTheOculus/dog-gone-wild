#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "LinkedListAPI.h"

typedef struct Entry {
    List* chain; /* Handle collisions via chaining */
} Entry;

typedef struct HashTable {
    int maxSize;
    int currentSize;
    Entry* entries; /* Each entry is a LinkedList */
} HashTable;

HashTable initializeHashTable(int size, char* (*printFunction)(void* toBePrinted), void (*deleteFunction)(void* toBeDeleted), int (*compareFunction)(const void* first, const void* second));
void deleteHashTable(HashTable* table);
void clearHashTable(HashTable* ht);
bool insertEntry(HashTable* ht, const char* key, void* data);
void deleteEntry(HashTable* ht, const char* key);
void* getEntry(HashTable* ht, const char* key);

#endif