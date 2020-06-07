#include "helpers.h"
#include <math.h>
#include <stdbool.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // iterate through i to get each row
    for (int i = 0; i < height; i++)
    {
        // iterate through j to get each character in row
        for (int j = 0; j < width; j++)
        {
            // find values of RGB
            // for example, row 1 is [0]: [0][1][2][3]
            float red = image[i][j].rgbtRed;
            float green = image[i][j].rgbtGreen;
            float blue = image[i][j].rgbtBlue;

            // add the values of RGB and find the average
            float maximum = red + green + blue;
            float average = round(maximum / 3);

            // implement back the colours into the RGB
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// for sepia, some values will be over the limit, thus we have to limit
int limit(int colour)
{
    if (colour > 255)
    {
        colour = 255;
    }
    return colour;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // iterate through i to get each row
    for (int i = 0; i < height; i++)
    {
        // iterate through j to get each character in row
        for (int j = 0; j < width; j++)
        {
            // find values of RGB
            // for example, row 1 is [0]: [0][1][2][3]
            float red = image[i][j].rgbtRed;
            float green = image[i][j].rgbtGreen;
            float blue = image[i][j].rgbtBlue;

            // calculate sepiaColours, and add limit function to prevent overflow
            float sepiaRed = limit(round((0.393 * red) + (0.769 * green) + (0.189 * blue)));
            float sepiaGreen = limit(round((0.349 * red) + (0.686 * green) + (0.168 * blue)));
            float sepiaBlue = limit(round((0.272 * red) + (0.534 * green) + (0.131 * blue)));

            // implement back the colours into the RGB
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // iterate through i to get each row
    for (int i = 0; i < height; i++)
    {
        // iterate through j to get each character in row
        for (int j = 0; j < width / 2; j++)
        {
            // for example, row 1 is [0]: [0][1][2][3]
            // we want to get the result  [3][2][1][0]
            RGBTRIPLE temp;

            // assign first value to temp array
            temp = image[i][j];

            // begin swapping values
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // create a temporary array duplicate of the picture
    RGBTRIPLE temp[height][width];
    float red;
    float green;
    float blue;
    int count;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // we have now pinpointed down to the location of the square
            /* we need to now highlight the surrounding characters
            the surrounding characters are basically,
            [i-1] [j-1, j, j+1]
            [i+0] [j-1, j, j+1]
            [i+1] [j-1, j, j+1] */

            // we need to give RGB values so that we can add the values in
            red = 0; green = 0; blue = 0; count = 0;

            for (int h = -1; h < 2; h++)
            {
                if (i + h < 0 || i + h > height - 1)
                {
                    continue;
                }

                for (int w = -1; w < 2; w++)
                {
                    if (j + w < 0 || j + w > width - 1)
                    {
                        continue;
                    }
                    red += image[i+h][j+w].rgbtRed;
                    green += image[i+h][j+w].rgbtGreen;
                    blue += image[i+h][j+w].rgbtBlue;
                    count++;
                }
            }
            temp[i][j].rgbtRed = round(red / count);
            temp[i][j].rgbtGreen = round(green / count);
            temp[i][j].rgbtBlue = round(blue / count);
        }
    }

    // copy values from the temporary table into the actual image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
        }
    }
    return;
}
