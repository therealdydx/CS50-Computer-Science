#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar k\n");
        return 1;
    }
    for (int j = 0, n = strlen(argv[1]); j < n; j++)
    {
        if (isdigit(argv[1][j]) == false)
        {
            printf("Usage: ./caesar k\n");
            return 1;
        }
    }
    
    int k = atoi(argv[1]);
    if (k < 0)
    {
        printf("Key cannot be negative. Please try again.\n");
        return 1;
    }
    
    string text = get_string("plaintext: ");
    printf("ciphertext: ");
    
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            if (isupper(text[i]))
            {
                printf("%c", (((text[i] - 'A') + k) % 26) + 'A');
            }
            else if (islower(text[i]))
            {
                printf("%c", (((text[i] - 'a') + k) % 26) + 'a');
            }
        }
        else
        {
            printf("%c", text[i]);
        }
    }
printf("\n");
}
