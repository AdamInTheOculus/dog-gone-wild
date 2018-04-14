#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 1
#ifdef DEBUG

#define log_error_exit(fmt, ...) {\
            fprintf(stderr, "ERROR ==> %s:%d %s() ==> " fmt, __FILE__, __LINE__, __func__, __VA_ARGS__);\
            exit(-1);\
        }
#endif

typedef struct HashItem {
    char key[100];
    void* data;
} HashItem;

typedef struct HashTable {
    int size;
    HashItem** items;
    void (*deleteData)(void* toBeDeleted);
} HashTable;

HashTable initializeHashTable(int size, void (*deleteFunction)(void* data));
void deleteHashTable(HashTable* table);

/** 
 *
 * @param string Represents some form of information label. 
 * @return A number representing the index of a table.
**/
unsigned int hash(char* string, unsigned int size);

#endif