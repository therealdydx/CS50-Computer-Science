#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
// Input the change owed into the programme
    float dollars;
    do
    {
    dollars = get_float("Change owed:");
    }
    while(dollars < 0);

// Convert cents to dollars
    int cents = round(dollars * 100);

// Initialize value of coins to be 0
    int coins = 0;

// If value is above certain value, deduct accordingly
    while (cents>=25)
    {
        cents -= 25;
        coins++;
    }

    while (cents>=10)
    {
        cents -= 10;
        coins++;
    }

    while (cents>=5)
    {
        cents -=5;
        coins++;
    }

    while (cents>=1)
    {
        cents -=1;
        coins++;
    }

    printf("%i", coins);
}
