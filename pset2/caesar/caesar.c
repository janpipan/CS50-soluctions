#include <stdio.h>
#include <stdlib.h>

char *encrypt(char *plain_text, int key_value);

int main(int argc, char *argv[])
{
    // check if user input was correct
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    char *key = argv[1];
    // check if user key is correct
    for (; *key != '\0'; key++)
    {
        if (*key - 48 > 9 || *key - 48 < 0)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    // go to first char that is not '\0'
    key--;
    // get key value
    int key_value = 0;
    for (int i = 1; key != argv[1] - 1; key--)
    {
        key_value += (*key - 48) * i;
        i *= 10;
    }
    key_value = key_value % 26;

    // get user input for text
    char *input_text = malloc(200 * sizeof(char));
    // prompt user for text input
    printf("plaintext: ");
    scanf("%[^\n]", input_text);
    // get encrypted value
    char *out_text = encrypt(input_text, key_value);
    printf("ciphertext: ");
    printf("%s\n", out_text);
    // free char pointers
    free(out_text);
    free(input_text);
    return 0;
}


char *encrypt(char *plain_text, int key_value)
{
    // allocate memory for encrypted text
    char *cipher_text = calloc(200, sizeof(char));
    if (cipher_text == NULL)
    {
        return NULL;
    }
    // loop over plain text and encrypt chars
    for (int i = 0; *plain_text != '\0'; plain_text++)
    {
        if (*plain_text > 64 && *plain_text < 90)
        {
            if (*plain_text + key_value > 90)
            {
                cipher_text[i] = (*plain_text + key_value - 90) + 64;
            }
            else
            {
                cipher_text[i] = *plain_text + key_value;
            }
        }
        else if (*plain_text > 96 && *plain_text < 122)
        {
            if (*plain_text + key_value > 122)
            {
                cipher_text[i] = (*plain_text + key_value - 122) + 96;
            }
            else
            {
                cipher_text[i] = *plain_text + key_value;
            }
        }
        else
        {
            cipher_text[i] = *plain_text;
        }
        i++;
    }
    return cipher_text;
}