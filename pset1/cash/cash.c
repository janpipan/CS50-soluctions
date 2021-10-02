#include <stdio.h>
#include <cs50.h>
#include <math.h>


int minimum_coins(int change_owed);


int main(void)
{
    float change_owed;
    // prompt user for input until he inputs number greater than 0
    do
    {
        change_owed = get_float("Change owed: ");
    }
    while (change_owed <= 0);
    // update input to int
    int cents = round(change_owed * 100);
    // print result
    printf("%d\n", minimum_coins(cents));

    return 0;
}

int minimum_coins(int change_owed)
{
    // set counter for counting coins and set possible pennies
    int counter = 0;
    int possible_pennies[4] = {25, 10, 5, 1};
    // while change_owed is greater than 0 try to subtract coin value if result is bigger than 0 update counter
    while (change_owed > 0)
    {
        for (int i = 0; i < 4; i++)
        {
            if (change_owed - possible_pennies[i] >= 0)
            {
                change_owed -= possible_pennies[i];
                counter++;
                break;
            }
        }
    }
    return counter;
}