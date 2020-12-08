#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    // insert variables here
    long card_number;

    // get card number here
    do
    {
        card_number = get_long("Card Number: ");
    }
    while (card_number < 0);

    // now comes the part where Luhn's algorithm come into action

    // make a copy of the card number to play around with, and initialize variables
    long card_number_1 = card_number;
    int one_digit = 0;
    int two_digit = 0;
    int digit = 0;
    int product = 0;
    int sum = 0;
    int sum1 = 0;
    int sum2 = 0;
    int checking_digit = 0;

    // double the second digit and collect those numbers with a loop
    while (card_number_1 > 0)
    {
        // this gives you the last digit after dividing 10, and multiply
        digit = (card_number_1/10) % 10;
        product = digit * 2;

        // since the product may be two-digit, need to split it up
        if (product > 10)
        {
            two_digit = product % 10;
            product = two_digit + 1;
        }
        else if (product == 10)
        {
            product = 1;
        }
        //  gets the final product, and then deduct 2 digits away
        sum1 = sum1 + product;

        card_number_1 = card_number_1 / 100;
    }
    // create a new loop for the first digits, first creating number again
    long card_number_2 = card_number;
    while (card_number_2 > 0)
    {
        one_digit = card_number_2 % 10;
        sum2 = sum2 + one_digit;
        card_number_2 = card_number_2 / 100;
    }

    // now add both sums together and check if algo holds
    sum = sum1 + sum2;
    if (sum % 10 != 0)
    {
        printf("INVALID\n");
    }
    // if the sum is good check for validity
    else
    {
        // calculate the total number of digits in card number
        int total_number = 0;
        long card_number_3 = card_number;
        while (card_number_3 > 0)
        {
            card_number_3 = card_number_3 / 10;
            total_number++;

            if (card_number_3 < 100 && card_number_3 > 10)
            {
                checking_digit = card_number_3;
            }
        }

        // check if it is AMEX
        if (total_number == 15)
        {
            if (checking_digit >= 34 && checking_digit <= 35 )
            {
                printf("AMEX\n");
            }
            else if (checking_digit >= 37 && card_number <= 38)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }

        // check if it is mastercard
        else if (total_number == 16)
        {
            if (checking_digit >= 51 && checking_digit <= 56)
            {
                printf("MASTERCARD\n");
            }

        // check if it is visa
            else if (checking_digit >= 40 && checking_digit <= 50)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }

        // check if it is visa
        else if (total_number == 13)
        {
            if (total_number == 13 && (checking_digit >= 40 && checking_digit < 50))
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        // check if it is fraudulent
        else
        {
            printf("INVALID\n");
        }
    }
}
