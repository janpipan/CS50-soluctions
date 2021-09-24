#include <cs50.h>
#include <stdio.h>

// prints pyramid with a height from 1-8
void pyramid(int n);

int main(void)
{
    // gets users input for the height of the pyramid
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    pyramid(height);
    return 1;
}

void pyramid(int n)
{
    for (int i = 0; i < n; i++)
    {
        // prints spaces before the #
        for (int j = 0; j < n - i - 1; j++)
        {
            printf(" ");
        }
        // prints #
        for (int j = n - i - 1; j < n; j++)
        {
            printf("#");
        }
        // space in the middle
        printf("  ");
        // left part of the pyramid
        for (int j = n - i - 1; j < n; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}