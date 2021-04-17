#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <cs50.h>

// Variable Global
string ALPHABET = "abcdefghijklmnopqrstuvwxyz";

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        string key = argv[1];
        int key_lenght = strlen(key);

        if (key_lenght != 26)
        {
            printf("Please, enter a key that contains exactly 26 letters.\n");
            return 1;
        }

        // Checks if there is no repetition of letters or if there are digits in the key
        for (int index_letters_i = 0; index_letters_i < key_lenght; index_letters_i++)
        {
            if (isalpha(key[index_letters_i]) == false)
            {
                printf("Please, enter a key that contains exactly 26 characters without numeric digits and character.\n");
                return 1;
            }

            for (int index_letters_j = index_letters_i + 1; index_letters_j < key_lenght; index_letters_j++)
            {
                if ((key[index_letters_i] == key[index_letters_j ]) || (toupper(key[index_letters_i]) == key[index_letters_j])
                    || (tolower(key[index_letters_i]) == key[index_letters_j ]))
                {
                    printf("Please, enter a key that contains exactly 26 characters without repeating.\n");
                    return 1;
                }
            }
        }

        // Enter plaintext
        string plaintext = get_string("plaintext: ");

        // Performs the encryption process
        int plaintext_lenght = strlen(plaintext);
        char ciphertext[plaintext_lenght];

        for (int index_char = 0; index_char < plaintext_lenght; index_char++)
        {
            if (isupper(plaintext[index_char]) != 0)
            {
                for (int index_letters = 0; index_letters <= 26; index_letters++)
                {
                    if (ALPHABET[index_letters] == tolower(plaintext[index_char]))
                    {
                        ciphertext[index_char] = toupper(key[index_letters]);
                    }
                }
            }

            else if (islower(plaintext[index_char]) != 0)
            {
                for (int index_letters = 0; index_letters <= 26; index_letters++)
                {
                    if (ALPHABET[index_letters] == plaintext[index_char])
                    {
                        ciphertext[index_char] = tolower(key[index_letters]) ;
                    }
                }
            }

            else
            {
                ciphertext[index_char] = plaintext[index_char];
            }
        }

        ciphertext[plaintext_lenght] = '\0';

        // Prints the result
        printf("ciphertext: %s\n", ciphertext);
        return 0;
    }
    else
    {
        printf("Usage: ./substitution key.\n");
        return 1;
    }
}
