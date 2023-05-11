// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
#define HEADER_SIZE 44

typedef struct
{
    uint8_t header[HEADER_SIZE];
    int16_t sample;
} sound_t;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    sound_t sound;
    size_t bytes_read;
    float factor = atof(argv[3]);
    // int i = 0;

    // TODO: Copy header from input file to output file
    fread(sound.header, 1, HEADER_SIZE, input);
    fwrite(sound.header, 1, HEADER_SIZE, output);

    // TODO: Read samples from input file and write updated data to output file
    while ((bytes_read = fread(&sound.sample, sizeof(uint16_t), 1, input)) > 0)
    {
        uint16_t scaled_sample = (uint16_t)(sound.sample * factor);
        fwrite(&scaled_sample, sizeof(uint16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
