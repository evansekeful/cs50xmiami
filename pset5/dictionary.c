/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// definitions
typedef struct node
{
    char word[LENGTH+1];
    struct node* next;
} node;

#define MAX_HASH 125000

// global variables
int words = 0;
node* hashtable[MAX_HASH];

/**
 * Returns hash-value given a word.
 * Based on function found @ https://www.reddit.com/r/cs50/comments/1x6vc8/pset6_trie_vs_hashtable/
 */
int hashtf(char* tbh)
{
    unsigned int hash = 0;
    for (int i = 0, n = strlen(tbh); i < n; i++)
    {
        if (tbh[i] < 65 || tbh[i] > 90 || tbh[i] != 39)
        {
            tbh[i] = toupper(tbh[i]);
        }
        
        hash = (hash << 2) ^ tbh[i];
    }
    return hash % MAX_HASH;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // store copy and convert word to uppercase
    int len = strlen(word);
    char copy[len+1];
    for (int i = 0; i < len+1; i++)
    {
            copy[i] = word[i];
    }

    // hash index copy
    int index = hashtf(copy);
    
    // check if index points to a node
    if (hashtable[index] == NULL)
    {
        return false;
    }
    
    // create cursor to move through nodes
    node* cursor = hashtable[index];
    
    // compare copy to dictionary at hash index
    while (cursor != NULL)
    {
        if (strcmp(copy, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    
    //return "not found" if cursor reaches NULL
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // open dictionary file
    FILE* fp = fopen(dictionary, "r");
    
    // check if file is NULL, else false
    if (fp == NULL)
    {
        printf("Could not open dictionary file.\n");
        return false;
    }
    
    // create word buffer
    char word[LENGTH+1];
    
    // scan file
    while (fscanf(fp, "%s\n", word) != EOF)
    {
        // malloc new node
        node* new_node = malloc(sizeof(node));
        
        //null terminate word
        word[strlen(word)] = '\0';

        // hash index word
        int index = hashtf(word);
        
        // load word into node
        strcpy(new_node->word, word);
        
        // insert node into hash table
        if (hashtable[index] == NULL)
        {
            hashtable[index] = new_node;
            new_node->next = NULL;
        }
        else
        {
            new_node->next = hashtable[index];
            hashtable[index] = new_node;
        }
        // increment size
        words++;
    }  
    
    // close file
    int fclose(FILE* fp);
    
    // return "loaded"
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return words;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // iterate through hashtable looking for nodes
    for (int i = 0; i < MAX_HASH; i++)
    {
        // set cursor
        node* cursor = hashtable[i];
        
        // free nodes if present
        while (cursor != NULL)
        {
            node* temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    
    words = 0;
    
    return true;
}