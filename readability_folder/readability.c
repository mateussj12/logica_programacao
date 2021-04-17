#include <cs50.h>
#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Prototypes
int count_letters(string text);
int count_words(string text);
int count_sentence(string text);

// Main function
int main(void)
{
    string text = get_string("Enter text: ");

    int result_letters = count_letters(text);
    int result_words = count_words(text);
    int result_sentence = count_sentence(text);

    // Calculates the index
    float l = (float) result_letters * (100 / (float) result_words);
    float s = (float) result_sentence * (100 / (float) result_words);
    int grade = round((0.0588 * l) - (0.296 * s) - 15.8);

    // Checks the grades
    if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade <= 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }

}

// Function to calculate letters
int count_letters(string text)
{
    int count_letters = 0;
    int lenght_text = strlen(text);

    for (int index_text = 0; index_text < lenght_text; index_text++)
    {
        if ((text[index_text] >= 'a' && text[index_text] <= 'z') || (text[index_text] >= 'A' && text[index_text] <= 'Z'))
        {
            count_letters++;
        }
    }

    return count_letters;
}

// Function to calculate words
int count_words(string text)
{
    int count_words = 0;
    int lenght_text = strlen(text);

    for (int index_text = 0; index_text < lenght_text; index_text++)
    {
        if (text[index_text] == 32)
        {
            count_words++;
        }
    }
    count_words++;

    return count_words;
}

// Function to calculate sentences
int count_sentence(string text)
{
    int count_sentence = 0;
    int lenght_text = strlen(text);

    for (int index_text = 0; index_text < lenght_text; index_text++)
    {
        if (text[index_text] == 33 || text[index_text] == 46 || text[index_text] == 63)
        {
            count_sentence++;
        }
    }
    return count_sentence;
}

