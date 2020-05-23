#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // WE WILL ATTEMPT TO CLEAN UP THE INPUT HERE:
    // check if the user provided 2 arguments or not
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // check if 26 characters
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // check if the string contains only characters
    for (int i = 0; i < 26; i++)
    {
        if (isalpha(argv[1][i]) == false)
        {
            printf("Key must contain 26 characters.");
            return 1;
        }
    } // initial checks have completed

    // initialize a variable for uppercase and lowercase, create 2D array
    char argument[3][26];
    for (int i = 0; i < 26; i++)
    {
        argument[0][i] = 'A' + i;
        argument[1][i] = argv[1][i];
        argument[2][i] = 'a' + i;
    }

    // check for repeated characters
    for (int i = 0; i < 26; i++)
    {
        int count = 0;
        for (int j = 0; j < 26; j++)
        {
            if (toupper(argument[1][j]) == toupper(argument[1][i]))
            {
                count++;
                if (count > 1)
                {
                    printf("Key must contain 26 unique characters.");
                    return 1;
                }
            }
        }
    }

/* CONVERSION ALGORITHM IS HERE:

    FIRST, LET'S PUT OUT A HYPOTHETICAL SITUATION TO DEDUCE A WORKING ALGORITHM:

    assume that our argv inputed argument is

    Random Translation: ATHERI > [0][1, 2, 3, 4, 5, 6] where argv[0][1 - 26]
                        ASCII char: [65,84,72,69,82,73]

    Translation Theory: ABCDEF > [1][1, 2, 3, 4, 5, 6] where argv[1][1 - 26]
                        ASCII char: [65,66,67,68,69,70]

    so if i input
                                       [4, 0, 1, 2, 3, 4]
    Input Characters: R A T H E R > [0][65,84,72,69,82,73]
    Print Characters: E A B C D E > [1][69,65,66,67,68,69]
                                       [4, 0, 1, 2, 3, 4]

    thus, we can see formula is argv[0][i] == argv[1][i]

    in short, to convert, we have the following:
    argv[0][i], where i is 1 - 26
    argv[0][i] is the ciphered text provided, and argv[1][i] is standard alphabet, in 2D array

    thus, we check that plaintext[i] == argv[0][i], and if there is a match
    simply print argv[1][i] for solution
*/

    // get plain text
    string plaintext = get_string("plaintext: ");
    // print cipher text
    printf("ciphertext: ");

    // check the characters for letters
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if (isalpha(plaintext[i]))
        {
            if (isupper(plaintext[i]))
            {
                for (int j = 0; j < 26; j++)
                {
                    if (toupper(argument[0][j]) == plaintext[i])
                    {
                        printf("%c", toupper(argument[1][j]));
                    }
                }
            }
            // if the character is lowercase
            if (islower(plaintext[i]))
            {
                for (int j = 0; j < 26; j++)
                {
                    if (tolower(argument[2][j]) == plaintext[i])
                    {
                        printf("%c", tolower(argument[1][j]));
                    }
                }
            }
        }
            // if the character is other than a letter i.e. ! ?
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
    return 0;
}