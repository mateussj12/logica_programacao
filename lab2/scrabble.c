#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    printf("--------- SCRABBLE ---------\n");
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");
    printf("\n");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if (score1 > score2)
    {
        printf("----------- WINNER -----------\n");
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("----------- WINNER -----------\n");
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("----------- WINNER -----------\n");
        printf("Tier!\n");
    }
}
// Compute points
int compute_score(string word)
{
    int score = 0;
    int number = 0;

    int length = strlen(word);

    for (int index = 0; index < length; index++)
    {
        if (isupper(word[index]))
        {
            number = POINTS[word[index] - 65];
            score += number;
        }
        else if (islower(word[index]))
        {
            number = POINTS[word[index] - 97];
            score += number;
        }
        else
        {
            number = 0;
        }

    }
    return score;
}

