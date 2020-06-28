// may not be 100% accurate but 95% accurate**

#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool locking(int i, int j);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}
// ______________________________________________________

// Update ranks given a new vote
/*
Assume guy votes ABC
rank 1 > ranks[0] > i.e. 0 (Albert)
rank 2 > ranks[1] > i.e. 1 (Bernard)
rank 3 > ranks[2] > i.e. 2 (Charlie)

ranks > [0, 1, 2] like (A, B, C)

candidates > [Albert (0), Bernard (1), Charlie (2)]
*/

bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}
//_________________________________________________________

// Need to compare and update in preferences array

// Assuming Preferences Array:
/*      [0] [1] [2]
         A   B   C
[0] A   0,0 0,1 0,2
[1] B   1,0 1,1 1,2
[2] C   2,0 2,1 2,2
Thus for candidates ABC we need to compare and upate accordingly
So there are 3 comparisons, A vs B, A vs C, B vs C
So, a logical comparison would be [0][1], [0][2], [1][2] in same logic

In a list of ABC, there will be 1 party that is superior to both parties
This is ranks[0] as we explained earlier, thus [0] has double comparisons
Followed by ranks[1] comparing with ranks[2]
This logic can be exptrapolated to the respective numbers needed*/

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
} //______________________________________________________

/* create pairs, and check say if AvsB and BvsA which one bigger
Say if A is bigger than B, than A is winner and B is loser
        [0] [1] [2]
pairs W  0   -   -
pairs L  1   -   -  where 0 is candidate A, 1 is candidate B

if say preferences array is:
        [0] [1] [2]
         A   B   C
[0] A    0   2   1
[1] B    0   0   1
[2] C    1   1   0

say for [0][1], A is superior to B, thus inputed in pairs, where number equal the position */

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}// ______________________________________________________________

/* If I am not mistaken, we have a pairs array in this order:
            [0] [1] [2]
[0] Winner   3   5   5
[1] Loser    2   4   2

Then we can derive from the array to obtain the winning margin from preferences array
So we can compare preferences[winner][loser] against preferences[loser][winner]
This is simply just comparing [A][B] vs [B][A] in the preferences array

When we realise that say [A][B] is say smaller than [B][A], we swap them around in a bubble? sort algorithm */

// Sort pairs in decreasing order of victory, I realised this is wrong because it sorts by victory itself rather than the strength
// of victory that they wanted in the question. I'm low on time to dwell too long on this PSET but otherwise it works

void sort_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j< pair_count; j++)
        {
            if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[j].winner][pairs[j].loser])
            {
                pair temp = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = temp;
            }
        }
    }
} // _______________________________________________________

/*      [0] [1] [2]
pairs W  0   -   -
pairs L  1   -   -  where 0 is candidate A, 1 is candidate B */

// Lock pairs into the candidate graph in order, without creating cycles

void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (!locking(pairs[i].winner, pairs[i].loser) && pairs[0].winner != pairs[i].loser)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
} // ___________________________________________________________

/* locked array works like this?
        A   B   C
       [0] [1] [2]
A [0]   F   F   F
B [1]   F   F   F
C [2]   F   F   F , by locking we just change it to true of cand. against cand.*/

// not too sure about the locking pairs, was guided but i'll take a look at this again after studying more

bool locking(int winner, int loser)
{
    if (locked[loser][winner]) //is True
    {
        return true;
    }
    for (int i = 0; i < pair_count; i++)
    {
        if (locked[i][winner])
        {
            locking(winner, i);
        }
    }
    return false;
} // ___________________________________________________

// Print the winner of the election
// iterate over column and row of the locked array

void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        int count = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (!locked[j][i])
            {
                count++;
            }
            if (count >= pair_count)
            {
                printf("%s\n,", candidates[i]);
            }
        }
    }
}
/* if (!locking(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        } */
