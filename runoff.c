#include <cs50.h>
#include <stdio.h>
#include <string.h>
// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// ________________________________________________

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

/* The idea behind this array is that:
    [0] [1] [2] [3]
[0] Tim Bob Jim
[1] Tim Jim ...
[2] Bob Jim ...
[3]
where going down vertical is the voter count
and going rightwards is the candidates present, or rather, the rank*/

// _________________________________________________

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

/* The idea behind this array is, assume candidates is:
    name / votes / eliminated
    [0] [1] [2]
[0] Tim  x   F
[1] Jim  y   F
[2] Bob  z   F
[3] Tom  a   F
where going down is candidates available, and leftwards is attributes */

// _________________________________________________

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

// __________________________________________________

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }

    // _____________________________________________

    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    // ______________________________________________

    // Check if the number of voters is above the maximum number

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // ______________________________________________

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            // Here we call the vote function and begin recording
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }
    // ______________________________________________

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}
// _____________________________________________________

bool vote(int voter, int rank, string name)
{
    for (int i =0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

/* So how does this function work? In short:
- When we called the vote function to test, we get_string of name
- We compared name gotten with the candidates array to find match
- In this case, we have to call a for loop to iterate down candidates array
- And if there is a match, recall the earlier query for votes
- We first queried for voters, then for candidates, so let's say if
- i = 0, j = 0 currently, this means we are at voter 1 rank 1
- assume Tim is voter 1 rank 1, we slot i into preferences[i][j]
- and we carry on as such, for all the ranks and then voters */

// _______________________________________________________

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (candidates[preferences[i][j]].eliminated == false)
            {
                candidates[preferences[i][j]].votes++;
                break;
            }
        }
    }
    return;
}
/* so how does this function work?
- If candidate is not eliminated, we count their votes.
- So we need to count all the rank 1's first of each voter
- We create 2 loops, one iterating over voter count and vice versa
- If we find that the voter 1 rank 1 is not eliminated, we add votes
- And we break, so that we can go to i = 1 i.e. voter 2 rank 1 */

// _______________________________________________________

// Print the winner of the election, if there is one
bool print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        string winner = candidates[i].name;
        if (candidates[i].votes > voter_count / 2)
        {
            printf("%s\n", winner);
            return true;
        }
    }
    return false;
}
// _________________________________________________________

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // We iterate through each one of the candidates
    // We assign a max value to a minumum vote counter
    // We continue assigning downwards as we go through candidates
    int vote_counter = voter_count;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false && candidates[i].votes < vote_counter)
        {
            vote_counter = candidates[i].votes;
        }
    }
    return vote_counter;
}
// ________________________________________________________

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false && candidates[i].votes != min)
        {
            return false;
        }
    }
    return true;
}
// ________________________________________________________

// Eliminate the candidate (or candidiates) in last place
void eliminate(int min)
{
    // Iterate through the candidates again
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
            // how this works is if true, then we don't add back
            // into the equation when we retabulate the votes
            // because of the conditional statement present in function
        }
    }
    return;
}
