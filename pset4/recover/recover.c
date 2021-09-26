#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Correct usage: ./recover file.raw");
        return 1;
    }
    // opens file for reading
    FILE *file = fopen(argv[1], "r");

    // if file cannot be opened
    if (file == NULL)
    {
        printf("File cannot be opened");
        return 2;
    }

    BYTE buffer[512];
    int signature[3] = {0xff, 0xd8, 0xff};
    int file_counter = 0;
    char out_file_name[9];
    FILE *output_file = NULL;

    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, file))
    {
        int new_picture = 0;
        // if fourth byte's first bits are 1110
        if ((buffer[3] & 0xe0) == 0xe0 && !(buffer[3] & (1 << 4)))
        {
            // if first three bytes are jpeg signature this block starts new picture
            for (int i = 0; i < 3; i++)
            {
                new_picture = buffer[i] == signature[i] ? 1 : 0;
            }
            // if signature is correct create new file
            if (new_picture)
            {
                // close previous file skip this step on first file
                if (file_counter != 0)
                {
                    fclose(output_file);
                }
                // set name for new file
                sprintf(out_file_name, "%03d.jpg", file_counter++);
                output_file = fopen(out_file_name, "w");
            }
        }
        // write block to outputfile
        if (output_file != NULL)
        {
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, output_file);
        }
    }

    // close input and output file
    fclose(file);
    fclose(output_file);
    return 0;
}