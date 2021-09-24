#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int start_size, end_size, years = 0;
    // TODO: Prompt for start size
    do
    {
        // if starting size is smaller than 9 prompt user again
        start_size = get_int("Start size: ");
    }
    while (start_size < 9);
    // TODO: Prompt for end size
    do
    {
        // if starting size is smaller than end size prompt user again
        end_size = get_int("End size: ");
    }
    while (start_size > end_size);
    // TODO: Calculate number of years until we reach threshold
    while (start_size < end_size)
    {
        // calculate how many llamas are born and how many of them pass away
        int born = (int)(start_size / 3);
        int pass_away = (int)(start_size / 4);
        // add new llammas to starting size
        start_size += born - pass_away;
        // increase year
        years++;
    }
    // TODO: Print number of years
    printf("Years: %d\n", years);
}