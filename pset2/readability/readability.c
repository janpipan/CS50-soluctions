#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

// prototypes
int get_words(string str);
int get_letters(string str);
int get_sentences(string str);

int main(void)
{
    // gets user input
    string user_input_string = get_string("Text: ");

    // calculates words, letters and sentences
    int words = get_words(user_input_string);
    int letters = get_letters(user_input_string);
    int sentences = get_sentences(user_input_string);

    // caluclates average letters per 100 words and average sentences per 100 words
    float average_letters = (float)letters / words * 100;
    float average_sentences = (float)sentences / words * 100;

    // calculates Coleman-Liau index
    float index = 0.0588 * average_letters - 0.296 * average_sentences - 15.8;

    // round index to get the grade
    int grade = (int)round(index);

    if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %d\n", grade);
    }

    return 0;
}

int get_words(string str)
{
    int counter = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        // if character is space count as a word
        if (str[i] == ' ')
        {
            counter++;
        }
    }
    // return counter +1 because of last word
    return ++counter;
}

int get_letters(string str)
{
    int counter = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        // if character is uppercase or lowercase letter increment counter
        if ((str[i] > 64 && str[i] < 91) || (str[i] > 96 && str[i] < 123))
        {
            counter++;
        }
    }
    return counter;
}

int get_sentences(string str)
{
    int counter = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        // if character is . or ! or ? count as end of sentence increment counter
        if (str[i] == '.' || str[i] == '!' || str[i] == '?')
        {
            counter++;
        }
    }
    return counter;
}
