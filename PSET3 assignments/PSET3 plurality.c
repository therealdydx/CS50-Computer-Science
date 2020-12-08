#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Make your custom data type, candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes, declare them first so that the main can run it
bool vote(string name);
void print_winner(void);

// declare main function with number of arguments and the arguments to be provided
int main(int argc, string argv[])
{
    // Check for invalid usage, if less than 2 means no names are declared
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;

    // if the candidate count is above the total number of candidates allowed
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }

    // add the candidate to the candidates array
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    // now get the total number of voters
    int voter_count = get_int("Number of voters: ");

    // Loop over all individual voters
    for (int i = 0; i < voter_count; i++)
    {
        // ask for the candidate that the voter has voted for 
        string name = get_string("Vote: ");

        // run the vote function to add vote, and check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election, run the print_winner function
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // count down the total number of candidates in the array
    for (int i = 0; i < candidate_count; i++)
    {
        // if both strings are identical, add to the vote count and return true
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election, void functions do not return a value
void print_winner(void)
{
    // initialize a winner variable
    int winner = 0;

    // count down the total number of candidates in the array
    for (int i = 0; i < candidate_count; i++ )
    {
        if (candidates[i].votes > winner)
        {
            winner = candidates[i].votes;
        }
    }
    // this is a linear search
    for (int i = 0; i < candidate_count; i++ )
    {
        if (candidates[i].votes == winner)
        {
            printf("%s\n", candidates[i].name);
        }
    }
    return;
}

