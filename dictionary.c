// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include "dictionary.h"
#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

unsigned int hash_value; // Initialise hash value

unsigned int word_count; // Initialise word count

// Hash table
node *table[N];

////////////////////////////////////////////////////////////////////

// we will give the hash function a word and the function will return a value which will be our indeks to a specific linked list.

////////////////////////////////////////////////// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r"); //Reads dictionary
    if (file == NULL) // IF false quit
    {
        return false;
    }

    // storage for one word
    char word[LENGTH + 1];

    // keep scanning for strings until end of file
    while (fscanf(file, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node)); //space for each node
        if (n == NULL)
        {
            return false;
        }
        // Copy word into the node's character field (which is called word, see structure of node at the top)
        strcpy(n->word, word);
        // Get hash value
        hash_value = hash(word);
        // new pointer definition
        n->next = table[hash_value];
        // let the new pointer be the head of next item in linked list.
        table[hash_value] = n;
        // Increment word count
        word_count++;
    }
// Close file
    fclose(file);
// If dict is loaded, return true
    return true;
}


/////////////////////////////////////////////// Hashes word to a number
unsigned int hash(const char *word) // Source: http://www.cse.yorku.ca/~oz/hash.html
{
    unsigned long hash = 5381;
    int c;
    while ((c = toupper(*word++))) // cite the source of this
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % N;
}

/////////////////////// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (word_count > 0)
    {
        return word_count; //if there are words return the count
    }
    return 0;
}



//////////////////////////////////// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    //hash value
    hash_value = hash(word);
    //access the specific linked list
    node *cursor = table[hash_value];
    //go through linked list
    while (cursor != NULL) // continue untill the end of the linked list
    {
        //check for word match
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        //move cursor to next node
        cursor = cursor->next;
    }

    return false;
}


//////////////// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // Iterate through buckets
    for (int i = 0; i < N; i++)
    {
        // For each bucket location set it to cursor
        node *cursor = table[i]; // header for the linkedlist
        // If cursor is true keep freeing
        while (cursor)
        {
            node *tmp = cursor;
            cursor = cursor->next;//moving cursor forward before freeing the node
            free(tmp);
        }
        if (i == N - 1 && cursor == NULL)
        {
            return true;
        }
    }
    return false;
}
