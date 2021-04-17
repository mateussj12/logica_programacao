#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <cs50.h>
#include <math.h>

// Main function
int main(int argc, string argv[])
{

    // Checks whether there is an integer in the key
    if (argc == 2 && isdigit(*argv[1]))
    {
        // Loop that checks for letters in the key
        for (int index = 0, confirmation = strlen(argv[1]); index < confirmation; index++)
        {
            int confirmed = isalpha(argv[1][index]);

            if (confirmed != 0)
            {
                printf("Usage: ./caesar key\n");
                return 2;
            }
        }

        int key = atoi(argv[1]);

        // Text that will be encrypted
        string plaintext = get_string("Plaintext: ");
        printf("ciphertext: ");

        // Performs the cryptonization process
        int lenght_text = strlen(plaintext);
        for (int index = 0; index < lenght_text; index++)
        {
            if (plaintext[index] >= 'a' && plaintext[index] <= 'z')
            {
                printf("%c", (((plaintext[index] - 'a') + key) % 26) + 'a');
            }

            else if (plaintext[index] >= 'A' && plaintext[index] <= 'Z')
            {
                printf("%c", (((plaintext[index] - 'A') + key) % 26) + 'A');
            }

            else
            {
                printf("%c", plaintext[index]);
            }
        }
        printf("\n");
        return 0;
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}



