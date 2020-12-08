// include the libraries
#include <cs50.h>
#include <stdio.h>

// include the main function to be run when program starts
int main(void)
{
  // create an integer n, to be used to assign a value from the input
  int n;

  // create a loop that will keep reiterating while input is not between 1 and 8
  do
  {
    // get the integer value 
    n = get_int("Height: ");
    
  } while(n < 1 || n > 8);

  // create a for loop that will keep building the pyramid

  // this loop is for horizontal side
  for (int i = 0; i < n; i++)
  {

    // this loop is for vertical side
    for (int j = 0; j < n; j++)
        
        // print a blank
        if(i + j < n - 1)
            printf(" ");
        
        // print a hashtag
        else
            printf("#");
    
    printf("\n");
  }

}

/* if input is 4, then the pyramid will work in this structure
   #
  ##
 ###
####

i.e. it will work in this format

 [0 1 2 3] [i]
0|0 1 2 3
1|1 2 3 4
2|2 3 4 5
3|3 4 5 6 
[j]

thus, it draws for values that are i + j > n - 1

iterate over j, so for first row, iterate over i
