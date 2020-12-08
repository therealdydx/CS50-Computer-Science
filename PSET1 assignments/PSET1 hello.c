// include libraries
#include <stdio.h>
#include <cs50.h>

// include the main function to be called when program runs
int main(void)
{
    // get user name
    string name = get_string("What is your name?\n");
    printf("hello, %s\n", name);
}

// the difference between main(void) or main() is that
// void is when main() takes no arguments
// while main() takes as many arguments as possible