#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
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

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int index_candidate = 0; index_candidate < candidate_count; index_candidate++)
    {
        if (strcmp(name, candidates[index_candidate]) == 0)
        {
            ranks[rank] = index_candidate;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int index_candidate_i = 0; index_candidate_i < candidate_count; index_candidate_i++)
    {
        for (int index_candidate_j = index_candidate_i + 1; index_candidate_j < candidate_count; index_candidate_j++)
        {
            preferences[ranks[index_candidate_i]][ranks[index_candidate_j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int index_candidate_i = 0; index_candidate_i < candidate_count; index_candidate_i++)
    {
        for (int index_candidate_j = index_candidate_i + 1; index_candidate_j < candidate_count; index_candidate_j++)
        {
            if (preferences[index_candidate_i][index_candidate_j] > preferences[index_candidate_j][index_candidate_i])
            {
                pairs[pair_count].winner = index_candidate_i;
                pairs[pair_count].loser = index_candidate_j;
                pair_count++;
            }
            else if (preferences[index_candidate_i][index_candidate_j] < preferences[index_candidate_j][index_candidate_i])
            {
                pairs[pair_count].winner = index_candidate_j;
                pairs[pair_count].loser = index_candidate_i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int index_i = 0; index_i < pair_count; index_i++)
    {
        int maximum = index_i;
        for (int index_j = index_i + 1; index_j < pair_count; index_j++)
        {
            if (preferences[pairs[index_j].winner][pairs[index_j].loser] > preferences[pairs[maximum].winner][pairs[maximum].loser])
            {
                maximum = index_j;
            }
        }
        pair temporary = pairs[index_i];
        pairs[index_i] = pairs[maximum];
        pairs[maximum] = temporary;
    }
    return;
}
// Create the circle and check the blocking of the winner or loser
bool cycle(int end, int cycle_start)
{
    if (end == cycle_start)
    {
        return true;
    }

    for (int index_i = 0; index_i < candidate_count; index_i++)
    {
        if (locked[end][index_i])
        {
            if (cycle(index_i, cycle_start))
            {
                return true;
            }
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int index_pairs = 0; index_pairs < pair_count; index_pairs++)
    {
        if (!cycle(pairs[index_pairs].loser, pairs[index_pairs].winner))
        {
            locked[pairs[index_pairs].winner][pairs[index_pairs].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool isLoser = false;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                isLoser = true;
                break;
            }
        }

        if (isLoser)
        {
            continue;
        }

        else if (!isLoser)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}
