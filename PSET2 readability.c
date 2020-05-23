#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
    // get the sentences first
    string text = get_string("Text: ");

    // initialize the variables and data types
    float letters = 0, words = 1, sentences = 0;

    // count the letters spaces and sentences
    for (int i = 0, n = strlen(text); i < n; i++)
        {
            if (isalpha(text[i]))
            {
                letters++;
            }
            if (isspace(text[i]))
            {
                words++;
            }
            if (text[i] == '.' || text[i] == '!' || text[i] == '?')
            {
            sentences++;
            }
        }

    // get the variables in the equation
    float l = letters / words * 100;
    float s = sentences / words * 100;
    float index = 0.0588 * l - 0.296 * s - 15.8;
    // round the index number to give an integer value of Grade
    int indexi = round(index);

    // for grade values
    if (indexi >= 1 && indexi <=16)
        {
            printf("Grade %i\n", indexi);
        }
    else
    {
        if (indexi < 1)
        {
            printf("Before Grade 1\n");
        }
        if (indexi > 16)
        {
            printf("Grade 16+\n");
        }
    }
}
