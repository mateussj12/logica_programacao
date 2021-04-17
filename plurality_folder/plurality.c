#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
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

// Function prototypes
bool vote(string name);
int get_max_votes(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters // Loop sobre todos os votantes
    for (int i = 0; i < voter_count; i++)
    {

        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int index = 0; index < candidate_count; index++)
    {
        if (strcmp(candidates[index].name, name) == 0)
        {
            candidates[index].votes++;
            return true;
        }

    }
    return false;
}

//Receives the maximum votes and assigns the variable
int get_max_votes(void)
{
    int maximum_votes = candidates[0].votes;
    for (int index = 0; index < candidate_count; index++)
    {
        if (candidates[index].votes > maximum_votes)
        {
            maximum_votes = candidates[index].votes;
        }
    }
    return maximum_votes;
}
// Print the winner (or winners) of the election
void print_winner(void)
{
    int maximum_votes = get_max_votes();
    for (int index = 0; index < candidate_count; index++)
    {
        if (candidates[index].votes == maximum_votes)
        {
            printf("%s\n", candidates[index].name);
        }
    }
}

