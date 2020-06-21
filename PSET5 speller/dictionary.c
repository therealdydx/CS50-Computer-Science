// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 10000;

// Hash table has been created
node *hashtable[N];

// create a counter so that can insert into the function
unsigned int count = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    char tmpword[strlen(word)]; // create a temp word
    strcpy(tmpword, word); // copy over the temp word

    // we must reduce the caps of every letter to pass the case-insensitive test on check50
    for (int i = 0; tmpword[i] != '\0'; i++)
    {
        tmpword[i] = tolower(tmpword[i]); // now change the char to caps insensitive
    }

    // determine location of word
    int location = hash(tmpword);

    // create a checker that identifies the probable hash value of the word and zeroes in on there
    node *checker = hashtable[location];

    // checker goes down linked list of the hastable index while the result is not NULL
    while (checker != NULL)
    {
        if (strcasecmp(checker->word, tmpword) == 0) // pointer points to a variable in the struct
        {
            return true; // checker has found a value
        }
        checker = checker->next; // checker goes to the next node
    }
    return false; // checker has not found the word in the dictionary matching with the text
}

// Hashes word to a number
unsigned int hash(const char* word)
{
    // hash function sourced from YouTube
    int hash = 0;
    int n;
    for (int i = 0; word[i] != '\0'; i++)
    {
        if (isalpha(word[i]))
        {
            n = word[i] - 'a' + 1;
        }
        else
        {
            n = 27;
        }
        hash = ((hash << 3) + n) % N;
    }
    return hash;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *infile = fopen(dictionary, "r"); // we open a file to read

    if (infile == NULL) // if NULL, return false
    {
        return false;
    }

    // reset the hash table so we can start putting words into the table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    char word[LENGTH + 1]; // declare new word in the function so it doesnt get undeclared identifier
    node *newnode; // declare node so that it doesnt the same as above

    while (fscanf(infile, "%s", word) != EOF) // where infile is stream of data, and word is sequence of characters
    // int fscanf(FILE *stream, const char *format [, argument, ...])
    {
        // if it is not the end of the file
        count++; // count the size of the dictionary
        do
        {
            newnode = malloc(sizeof(node));
            if (newnode == NULL)
            {
                free(newnode); // clear so we can start
            }
        }
        while (newnode == NULL);

        strcpy(newnode->word, word); // char* strcpy(char* destination, const char* source)
        int index = hash(word); // get a hash index for the word so we can put it in the table

        if (hashtable[index] == NULL) // create a new node in the table
        {
            newnode->next = NULL; // link the newnode next variable to NULL
            hashtable[index] = newnode; // link the newnode to the hashtable index
        }
        else
        {
            newnode->next = hashtable[index]; // add newnode to the 1st node in the linked list
            hashtable[index] = newnode; // change the hashtable index to point at newnode first
        }
    }
    fclose(infile); // we are done with the file
    return true; // return true as stated in the question if successful
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++) // clearing out all the buckets
    {
        node *cursor;
        cursor = hashtable[i]; // begin iterating down the hash table

        while (cursor)
        {
            node *tmp = cursor; // create a temporary node equals to the cursor
            cursor = cursor->next; // cursor goes to the next node in the list first
            free(tmp); // now the temporary node is freed, yet cursor is already at next list so not lost
        }
    }
    return true; // if fail, it should fail much earlier i believe
}
