#include <stdio.h>
#include <cs50.h>

enum
{
    AMEX,
    MASTERCARD,
    VISA,
    INVALID
};

int get_credit_card(long number);

int main(void)
{
    long number = get_long("Number: ");
    int credit_card = get_credit_card(number);
    if (credit_card == AMEX)
    {
        printf("AMEX\n");
    }
    else if (credit_card == MASTERCARD)
    {
        printf("MASTERCARD\n");
    }
    else if (credit_card == VISA)
    {
        printf("VISA\n");
    }
    else if (credit_card == INVALID)
    {
        printf("INVALID\n");
    }
    return 0;
}

int get_credit_card(long number)
{
    int counter = 1, sum = 0, num = 0, num_after;
    // loop over number digits
    for (long i = 10; i < number * 10; i *= 10)
    {
        // get digit
        num_after = num;
        num = (number % i) / (i / 10);
        // every second digit is multipled by 2
        if (counter % 2 == 0)
        {
            // if number is greater than 9 add two digits together
            if ((num * 2) > 9)
            {
                sum += (num * 2) % 10 + ((((num * 2) - ((num * 2) % 10)) % 100) / 10);
            }
            else
            {
                sum += num * 2;
            }
        }
        else
        {
            sum += num;
        }
        counter++;
    }
    // if sum ends with 0 card is valid
    if (sum % 10 == 0)
        {
          if (num == 3 && (num_after == 4 || num_after == 7) && counter - 1 == 15)
          {
               return AMEX;
          }
          if (num == 5 && (num_after > 0 && num_after < 6) && counter - 1 == 16)
          {
              return MASTERCARD;
          }
          if (num == 4 && (counter - 1  == 13 || counter - 1 == 16))
          {
              return VISA;
          }
        }
    return INVALID;
}