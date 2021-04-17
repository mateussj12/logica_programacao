// Implements a dictionary's functionality
#include <stdbool.h>
#include <strings.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "dictionary.h"

#define TABLE_HASH_SIZE 1000

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

//Number of words and hash loading
const unsigned int number_word;
bool load_dict;

// Hash table
node *table[TABLE_HASH_SIZE];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int hash = 0;
    int N;

    for (int index_hash = 0; word[index_hash] != '\0'; index_hash++)
    {
        if (isalpha(word[index_hash]))
        {
            N = (word[index_hash] - 97) + 1;
        }

        else
        {
            N = 27;
        }

        hash = ((hash << 3) + N) % TABLE_HASH_SIZE;
    }

    return hash;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    return false;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    return false;
}
