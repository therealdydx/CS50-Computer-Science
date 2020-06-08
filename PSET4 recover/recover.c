#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // check the number of arguments
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }
    // open memory card
    FILE *file = fopen(argv[1], "r");

    // check if file is wrong
    if (file == NULL)
    {
        return 1;
    }

    // create some variables for the task
    FILE *img = NULL; // create the file to host these attributes below
    char filename[8]; // we have to create a filename ---.jpg which is 7 characters
    BYTE *buffer = malloc(512 * sizeof(BYTE)); // create a temporary buffer to store images
    int count = 0;

    /* use fread(data, size, number, inptr) to read data, where inptr is pointer to file where data is read,
    size is size of each element, number is number of elements, and data is a pointer ot the buffer where data is stored*/
    
    
    if (buffer == NULL)
    {
        return 1; 
    } // check for memory leaks
    
    while (fread(buffer, 512, 1, file) == 1)
    {
        // check if it is a JPEG, 0xff, 0xd8, 0xff, and 0xe_

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // close the previous JPEG file if there is
            if (count > 0)
            {
                fclose(img);
            }

            // start of a new JPEG, create filename and add to count
            sprintf(filename, "%03i.jpg", count);
            img = fopen(filename, "w");

            // check for errors, because it will cause segfault on check50
            if (img == NULL)
            {
                fclose(file);
                fprintf(stderr, "Cannot create image");
                return 3;
            }

            count++;
        }

        // write JPEG file
        if (count > 0)
        {
                fwrite(buffer, 512, 1, img); //write to buffer
        }
    }
    // free memory here
    fclose(img);
    fclose(file);
    free(buffer);
    
    return 0;
}