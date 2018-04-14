/**
 * @file hashtable.c
 * @author Adam Sinclair
 * @created Sun April 8 2018
 * @purpose Implementation of HashTable
**/

#include "HashTableAPI.h"

/** 
 * Implement FNV-1a hash algorithm
 * https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
 *
 * @param string Represents a label for some information.
 * @param size Size of hash table used for modulo operation.
 * @return A non-zero number representing the index in a table.
**/
static unsigned int hash(char* string, unsigned int size);

HashTable initializeHashTable(int size, char* (*printFunction)(void* toBePrinted), void (*deleteFunction)(void* toBeDeleted), int (*compareFunction)(const void* first, const void* second)){
    if(size < 1)
        log_error_exit("Size parameter is invalid: [%d]", size);
    if(deleteFunction == NULL || printFunction == NULL || compareFunction == NULL)
        log_error_exit("HashTable with size [%d] has NULL function pointer.", size);

    HashTable ht;
    ht.size = size;

    // Allocate space for the array of entries
    if((ht.entries = calloc((size_t)ht.size, sizeof(Entry))) == NULL)
        log_error_exit("Initializing hash table of size [%d] failed due to malloc error.", size);

    // For each entry, initialize the chain
    for(int i=0; i<ht.size; i++)
        ht.entries[i].chain = initializeList(printFunction, deleteFunction, compareFunction);

    return ht;
}

void deleteHashTable(HashTable* ht)
{
    if(ht == NULL)
        return;

    for(int i=0; i<ht->size; i++)
    {
        Entry* entry = NULL;
        entry = &ht->entries[i];

        if(entry != NULL)
        {
            clearList(&entry->chain);
            entry = NULL;
        }
    }

    free(ht->entries);
}

static unsigned int hash(char* string, unsigned int size)
{
    if(string == NULL || strlen(string) < 1)
        return 0;

    int len = strlen(string);
    unsigned long hash = 2166136261u;

    for(int i=0; i<len; i++)
    {
        hash ^= string[i];
        hash *= 16777617u;
    }

    return hash % size;
}