/**
 * @file hashtable.c
 * @author Adam Sinclair
 * @created Sun April 8 2018
 * @purpose Implementation of HashTable
**/

#include "HashTableAPI.h"
#include "debug.h"

static unsigned int hash(const char* string, unsigned int size);

HashTable initializeHashTable(int size, char* (*printFunction)(void* toBePrinted), void (*deleteFunction)(void* toBeDeleted), int (*compareFunction)(const void* first, const void* second)){
    if(size < 1)
        log_error_exit("Size parameter is invalid: [%d]", size);
    if(deleteFunction == NULL || printFunction == NULL || compareFunction == NULL)
        log_error_exit("HashTable with size [%d] has NULL function pointer.", size);

    HashTable ht;
    ht.maxSize = size;
    ht.currentSize = 0;

    // Allocate space for the array of entries
    if((ht.entries = calloc((size_t)ht.maxSize, sizeof(Entry))) == NULL)
        log_error_exit("Allocating hash table of size [%d] failed.", size);

    // For each entry, initialize the chain
    for(int i=0; i<ht.maxSize; i++)
    {
        ht.entries[i].chain = initializeList(printFunction, deleteFunction, compareFunction);
        //log_debug("List address: %p\n", &ht.entries[i].chain);
    }

    return ht;
}

void deleteHashTable(HashTable* ht)
{
    if(ht == NULL)
        return;

    for(int i=0; i<ht->maxSize; i++)
    {
        Entry* entry = NULL;
        entry = &ht->entries[i];

        if(entry != NULL)
        {
            clearList(entry->chain);
            entry = NULL;
        }
    }

    free(ht->entries);
}

void clearHashTable(HashTable* ht)
{
    if(ht == NULL)
        return;

    for(int i=0; i<ht->maxSize; i++)
    {
        Entry* entry = NULL;
        entry = &ht->entries[i];

        if(entry != NULL)
        {
            clearList(entry->chain);
            entry = NULL;
        }
    }
}

bool insertEntry(HashTable* ht, const char* key, void* data)
{
    if(ht == NULL || ht->maxSize <= 0) {
        log_error("%s", "HashTable is NULL or has no space.\n");
        return false;
    } else if(key == NULL) {
        log_error("%s", "Key is NULL or empty.\n");
        return false;
    } else if(data == NULL) {
        log_error("%s", "Data is NULL.\n");
        return false;
    }

    // Get hashcode from key and insert into entry chain
    int hashValue = hash(key, ht->maxSize);
    log_debug("Hashing entry with value: %d\n", hashValue);

    // Check if node with key already exists
    if(getEntry(ht, key) != NULL)
    {
        log_debug("Entry with key [%s] already exists. Nothing added.\n", key);
        return false;
    }

    insertBack(ht->entries[hashValue].chain, data, key);
    ht->currentSize++;
    return true;
}

void* getEntry(HashTable* ht, const char* key)
{
    if(ht == NULL || ht->maxSize <= 0) {
        log_error("%s", "HashTable is NULL or has no space.\n");
        return NULL;
    } else if(key == NULL) {
        log_error("%s", "Key is NULL or empty.\n");
        return NULL;
    }

    int hashValue = hash(key, ht->maxSize);
    return findElement(*ht->entries[hashValue].chain, key);
}

void deleteEntry(HashTable* ht, const char* key)
{
    if(ht == NULL || ht->maxSize <= 0) {
        log_error("%s", "HashTable is NULL or has no space.\n");
        return;
    } else if(key == NULL) {
        log_error("%s", "Key is NULL or empty.\n");
        return;
    }

    // Get hashcode from key
    int hashValue = hash(key, ht->maxSize);
    log_debug("Delete entry with value: %d\n", hashValue);

    // Find data element from LinkedList
    void* data = findElement(*ht->entries[hashValue].chain, key);
    if(data == NULL)
        return;
    
    // Delete node from entry chain
    data = deleteDataFromList(ht->entries[hashValue].chain, key);

    // Delete data from Data struct
    ht->entries[hashValue].chain->deleteData(data);
    ht->currentSize--;
}

/** 
 * Implement FNV-1a hash algorithm
 * https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
 *
 * @param string Represents a label for some information.
 * @param size Size of hash table used for modulo operation.
 * @return A non-zero number representing the index in a table.
**/
static unsigned int hash(const char* string, unsigned int size)
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
