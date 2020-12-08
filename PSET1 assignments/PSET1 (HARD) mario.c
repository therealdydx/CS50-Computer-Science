// include the libraries 
#include <stdio.h>
#include <cs50.h>

// create a function
void print(char c, int j)
{
    for (int i = 0; i < j; i++)
    {
        printf("%c", c);
    }
}

// include main() the function to be run
int main(void)
{
    // get the number for which to build the 2 sided pyramid 
    int n;
    do
    {
        n = get_int("Height: ");
    }
    
    // since inclusive values are between 1 and 8
    while (n < 1 | n > 8);

    // now begins the construction of the pyramid
    
    /* LOGIC:
      #  # 
     ##  ##
    ###  ###
    this is equivalent to:
    1 2 3* 4 5 6* 7 8, so 2 spaces, 1 hash, 2 spaces, 1 hash
    1 2*3* 4 5 6* 7*8, so 1 space, 2 hashes, 2 spaces, 2 hashes
    1*2*3* 4 5 6* 7*8*, so 0 space, 3 hashes, 2 spaces, 3 hashes
    
    aka can put to
                   blank  hash blank hash
    n = 3, i = 0 > n-1-i | 1+i | 2 | 1+i
    n = 3, i = 1 > n-1-i | 1+i | 2 | 1+i
    n = 3, i = 2 > n-1-i | 1+i | 2 | 1+i
    */
    
    for (int i = 0; i < n; i++)
    {
        // print the blank spaces
        print(' ', n-1-i);
        
        // print the hashes when necessary
        print('#', i+1);
        
        // there's a blank in the middle of the pyramid
        print(' ', 2);
        
        // print out the hashes for the final few 
        print('#', i+1);
        
        printf("\n");
    }
}      
