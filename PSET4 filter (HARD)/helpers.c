#include "helpers.h"
#include <math.h>

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

int limit(int colour)
{
    if (colour > 255)
    {
        colour = 255;
    }
    return colour;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    float xRed; float xGreen; float xBlue;
    float yRed; float yGreen; float yBlue;

    // create a temporary table to not alter calculations
    RGBTRIPLE temp[height][width];

    // iterate down each character
    for(int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            xRed = 0; xGreen = 0; xBlue = 0;
            yRed = 0; yGreen = 0; yBlue = 0;

            // just like the easier pset, check the matrix
            /* we need to now highlight the surrounding characters
            the surrounding characters are basically,
            [i-1] [j-1, j, j+1]
            [i+0] [j-1, j, j+1]
            [i+1] [j-1, j, j+1] */

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
                    /* we need to create a Gx and Gy factor
                    we can create a factor by referring to the array*/
                    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
                    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

                    // calculating x values with factor
                    xRed += image[i+h][j+w].rgbtRed * Gx[h+1][w+1];
                    xGreen += image[i+h][j+w].rgbtGreen * Gx[h+1][w+1];
                    xBlue += image[i+h][j+w].rgbtBlue * Gx[h+1][w+1];

                    // calculating y values with factor
                    yRed += image[i+h][j+w].rgbtRed * Gy[h+1][w+1];
                    yGreen += image[i+h][j+w].rgbtGreen * Gy[h+1][w+1];
                    yBlue += image[i+h][j+w].rgbtBlue * Gy[h+1][w+1];
                }
            }

            temp[i][j].rgbtRed = limit(round(sqrt((xRed * xRed) + (yRed * yRed))));
            temp[i][j].rgbtGreen = limit(round(sqrt((xGreen * xGreen) + (yGreen * yGreen))));
            temp[i][j].rgbtBlue = limit(round(sqrt((xBlue * xBlue) + (yBlue * yBlue))));
        }
    }

    // iterate through the temporary values
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
