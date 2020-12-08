#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>

// argc is the number of arguments -> ./caesar 2 is 2 arguments
int main(int argc, string argv[])
{
    // if the argument count is not 2, then answer is wrong
    if (argc != 2)
    {
        printf("Usage: ./caesar k\n");
        return 1;
    }

    // now to get the second value in argv
    for (int j = 0, n = strlen(argv[1]); j < n; j++)
    {

        // this is to check if there are any letters in any part of the second character
        if (isdigit(argv[1][j]) == false)
        {
            printf("Usage: ./caesar k\n");
            return 1;
        }
    }
    
    // takes a string and returns an int
    int k = atoi(argv[1]);
    if (k < 0)
    {
        printf("Key cannot be negative. Please try again.\n");
        return 1;
    }
    
    string text = get_string("plaintext: ");
    printf("ciphertext: ");
    
    // now begin the conversion process
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        
        // if it is a text
        if (isalpha(text[i]))
        {
            
            // if it is uppercase
            if (isupper(text[i]))
            {
                printf("%c", (((text[i] - 'A') + k) % 26) + 'A');
            }

            // if it is lowercase
            else if (islower(text[i]))
            {
                printf("%c", (((text[i] - 'a') + k) % 26) + 'a');
            }
        }

        // else if it is something like a full stop, a punctuation, etc
        else
        {
            printf("%c", text[i]);
        }
    }
printf("\n");
}
