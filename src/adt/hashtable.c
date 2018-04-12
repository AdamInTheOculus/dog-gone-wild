/**
 * @file hashtable.c
 * @author Adam Sinclair
 * @created Sun April 8 2018
 * @purpose Implementation of HashTable
**/

#include "hashtable.h"

/**
 * @purpose Statically creates new HashTable struct. Each individual node
 *          is dynamically allocated.
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

int hashKey(char* string)
{
    if(string == NULL || strlen(string) < 1)
        return -1;

    return 0;
}