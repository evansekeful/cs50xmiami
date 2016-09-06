/**
 * Unit testing for dictionary.c
 * ./tester dictionaries/small texts/sample.txt
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

#define MAX_HASH 65536

// global variables
int words = 0;
node* hashtable[MAX_HASH];

// prototypes
int hashtf(char* tbh); // hash
int checker(FILE* fp); //spell checker
bool load(const char* dictionary); // load
bool check(const char* word); // check

int main(int argc, char* argv[]) //argv[1] = dictionary, argv[2] = sample test
{
    // load dictionary
    char* dictionary = argv[1];
    bool loaded = load(dictionary);
    
    if (!loaded) //use loaded variable
    {
        return 1;
    }
    
    // open text
    char* text = argv[2];
    FILE* check = fopen(text, "r");
    
    // run spellcheck function
    int misspelled = checker(check);
    
    printf("%i\n", misspelled);
    
    return 0;
}

    
/** 
 * TODO 
 * 1. check characters of strings are being copied over.
 * 2. check what the hash function returns against string
 * 3. check if linked lists are being properly indexed/built
 **/
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
        word[strlen(word)] = '\0'; //FIX

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
 * TODO 
 * 1. check which characters of strings are being copied over.
 * 2. check what the hash function returns against string
 * 3. check if linked lists are being properly indexed/built
 **/
 
bool check(const char* word)
{
    // store copy of word
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

int checker(FILE* fp)
{
    int index = 0, misspellings = 0;
    char word[LENGTH+1];
    
    for (int c = fgetc(fp); c != EOF; c = fgetc(fp))
    {
        // allow only alphabetical characters and apostrophes
        if (isalpha(c) || (c == '\'' && index > 0))
        {
            // append character to word
            word[index] = c;
            index++;
    
            // ignore alphabetical strings too long to be words
            if (index > LENGTH)
            {
                // consume remainder of alphabetical string
                while ((c = fgetc(fp)) != EOF && isalpha(c));
    
                // prepare for new word
                index = 0;
            }
        }
    
        // ignore words with numbers (like MS Word can)
        else if (isdigit(c))
        {
            // consume remainder of alphanumeric string
            while ((c = fgetc(fp)) != EOF && isalnum(c));
    
            // prepare for new word
            index = 0;
        }
    
        // we must have found a whole word
        else if (index > 0)
        {
            // terminate current word
            word[index] = '\0';
    
            // update counter
            words++;
    
            // check word's spelling
            bool misspelled = !check(word);
    
            // print word if misspelled
            if (misspelled)
            {
                printf("%s\n", word);
                misspellings++;
            }
    
            // prepare for next word
            index = 0;
        }
    }
    
    return misspellings;
}
