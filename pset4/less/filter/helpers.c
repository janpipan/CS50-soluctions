#include "helpers.h"
#include <string.h>
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // loops over image array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // gets average value of RGB value
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = (int)round((image[i][j].rgbtRed +
                                  image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // loops over image array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // get RGB values
            int red = image[i][j].rgbtRed, green = image[i][j].rgbtGreen, blue = image[i][j].rgbtBlue;
            // calculates sepia RGB values
            int sepia_red = (int)round((.393 * red + .769 * green + .189 * blue));
            int sepia_green = (int)round((.349 * red + .686 * green + .168 * blue));
            int sepia_blue = (int)round((.272 * red + .534 * green + .131 * blue));
            // cap value at 255 and set it to image
            image[i][j].rgbtRed = sepia_red > 255 ? 255 : sepia_red;
            image[i][j].rgbtGreen = sepia_green > 255 ? 255 : sepia_green;
            image[i][j].rgbtBlue = sepia_blue > 255 ? 255 : sepia_blue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        RGBTRIPLE temp;
        int counter = width - 1;
        // loop over half picture
        for (int j = 0; j < width / 2; j++)
        {
            // switch pixel on left side with the pixel on the right side
            temp = image[i][j];
            image[i][j] = image[i][counter];
            image[i][counter--] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // blured image array 
    RGBTRIPLE blured_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int value_counter = 0, red = 0, green = 0, blue = 0;
            // form 3x3 box around the pixel
            for (int row = -1; row < 2; row++)
            {
                for (int col = -1; col < 2; col++)
                {
                    // if pixel that forms a box is outside of array skip it
                    if (i + row < 0 || i + row == height || j + col < 0 || j + col == width)
                    {
                        continue;
                    }
                    // add RGB values to totals and for each valid pixel increase counter of how many pixels is in calculation
                    red += image[i + row][j + col].rgbtRed;
                    green += image[i + row][j + col].rgbtGreen;
                    blue += image[i + row][j + col].rgbtBlue;
                    value_counter++;
                }
            }
            // add pixel to blured pixel image array
            blured_image[i][j].rgbtRed = (int)round(red / (float)value_counter),
                              blured_image[i][j].rgbtGreen = (int)round(green / (float)value_counter),
                                                blured_image[i][j].rgbtBlue = (int)round(blue / (float)value_counter);
        }
    }
    // copy blured image array to image
    memcpy(image, blured_image, sizeof(blured_image));
    return;
}
