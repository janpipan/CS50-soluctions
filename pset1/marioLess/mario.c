#include <stdio.h>
#include <cs50.h>


void drawPyramid(int height);

int main(void)
{
    int height;
    // prompt user for input until you get the correct input
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    drawPyramid(height);

    return 0;
}

void drawPyramid(int height)
{
    for (int i = 0; i < height; i++)
    {
        // prints spaces before #
        for (int j = height - 1 - i; j > 0; j--)
        {
            printf(" ");
        }
        // prints #
        for (int j = i + 1; j > 0; j--)
        {
            printf("#");
        }
        // got to new line
        printf("\n");
    }
}