// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 100;

// Hash table
node *table[N];

// word counter
unsigned int counter = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // get hash of word
    unsigned int word_hash = hash(word);
    // set node to first node on table with hash number
    node *n = table[word_hash];
    if (n == NULL)
    {
        return false;
    }
    while (1)
    {
        // if word is in dictionary return true
        if (strcasecmp(n->word, word) == 0)
        {
            return true;
        }
        // if this is last node in linked list break
        if (n->next == NULL)
        {
            break;
        }
        n = n->next;
    }
    return false;
}

// Hashes word to a number
// sdbm hash function
// source http://www.cse.yorku.ca/~oz/hash.html

unsigned int hash(const char *word)
{
    unsigned int h = 0;
    int c;

    while ((c = tolower(*word++)))
    {
        h = c + (h << 6) + (h << 16) - h;
    }

    return h % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // opens dictionary for reading
    FILE *file = fopen(dictionary, "r");
    // if file cannot be opened return false
    if (file == NULL)
    {
        return false;
    }
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }
    char word[LENGTH + 1];
    // do until it reaches end of file
    while (fscanf(file, "%s", word) != EOF)
    {
        // allocate memory for node
        node *n = malloc(sizeof(node));
        // if memory cannot be allocated return false
        if (n == NULL)
        {
            return false;
        }
        // add word to node
        strcpy(n->word, word);
        // calculate hash for word
        unsigned int word_hash = hash(word);
        // set nodes next node to previous first node in table
        n->next = table[word_hash];
        // set current node to fist node
        table[word_hash] = n;
        // increase counter
        counter++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // loops over table
    for (int i = 0; i < N; i++)
    {
        // set node to first node in i-th position in table
        node *n = table[i];
        if (n == NULL)
        {
            continue;
        }
        // stop when nodes next node is null
        while (1)
        {
            // if this is last node free it and exit loop
            if (n->next == NULL)
            {
                free(n);
                break;
            }
            // set tmp node to current node
            node *tmp = n;
            // set node to next node
            n = n->next;
            // free current node
            free(tmp);
        }
    }
    return true;
}
