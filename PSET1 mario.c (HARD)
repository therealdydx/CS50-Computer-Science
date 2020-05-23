#include <stdio.h>
#include <cs50.h>

void print(char c, int j)
{
    for (int i = 0; i < j; i++)
    {
        printf("%c", c);
    }
}

int main(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    
    while (n < 1 | n > 8);

    for (int i = 0; i < n; i++)
    {
        print(' ', n-1-i);
        print('#', i+1);
        print(' ', 2);
        print('#', i+1);
        
        printf("\n");
    }
}      

