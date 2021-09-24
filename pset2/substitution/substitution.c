#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

// prototypes
void print_encrypted(string input_string);
int set_encryption_offsets(string encryption_string);

// global variables
int encryption_offset[26];


int main(int argc, string argv[])
{
    // if program gets two arguments and second argument has length 26
    if (argc == 2 && (strlen(argv[1]) == 26))
    {
        // setting encryption offsets and checking if input string has valid characters
        if (set_encryption_offsets(argv[1]))
        {
            printf("Key must contain 26 unique letters!");
            return 1;
        }
        // get user input
        string user_input = get_string("plaintext: ");
        // encrypt message and print it
        print_encrypted(user_input);
        printf("\n");
    }
    else if (argc != 2)
    {
        printf("Program needs 2 command-line arguments\n");
        return 1;
    }
    else
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    return 0;
}

int set_encryption_offsets(string encryption_string)
{
    // array for checkin if value is already in string
    int is_in_string[26] = {0};
    for (int i = 0; i < 26; i++)
    {
        // if value is upper or lower case char
        if (((encryption_string[i] > 64 && encryption_string[i] < 91) || (encryption_string[i] > 96 && encryption_string[i] < 123)))
        {
            int character = tolower(encryption_string[i]);
            // if char is not in string
            if (!is_in_string[character - 97])
            {
                // add to string and add offset to encryption 
                is_in_string[character - 97] = 1;
                encryption_offset[i] = character - (97 + i);
            }
            else
            {
                return 1;
            }
        }
        else
        {
            return 1;
        }
    }
    return 0;
}

void print_encrypted(string input_string)
{
    printf("ciphertext: ");
    for (int i = 0; input_string[i] != '\0'; i++)
    {
        if (isupper(input_string[i]))
        {
            printf("%c", (int)input_string[i] + toupper(encryption_offset[(int)input_string[i] - 65]));
        }
        else if (islower(input_string[i]))
        {
            printf("%c", (int)input_string[i] + encryption_offset[(int)input_string[i] - 97]);
        }
        else
        {
            printf("%c", input_string[i]);
        }
    }
}

