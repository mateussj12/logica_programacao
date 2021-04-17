#include <cs50.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

// Size of the block that will be read and written
#define BLOCKSIZE 512

// Prototype
bool isHeaderJPG(uint8_t buffer_header[]);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover imagem\n");
        return 1;
    }

    char *inputFile = argv[1];

    // Open input file
    FILE *inputReady = fopen(inputFile, "r");
    if (inputReady == NULL)
    {
        printf("Could not open %s.\n", inputFile);
        return 2;
    }

    // Make space for jpg file name
    char image[8];

    // Pointer to outfile
    FILE *outputFile = NULL;

    // Number of image files created
    int imageCount = 0;

    uint8_t buffer[BLOCKSIZE];

    // search until jpg is found
    while (fread(buffer, sizeof(uint8_t), BLOCKSIZE, inputReady) || feof(inputReady) == 0)
    {
        if (isHeaderJPG(buffer))
        {
            // close image file if one has been created
            if (imageCount > 0)
            {
                fclose(outputFile);
            }

            // make name for image
            sprintf(image, "%03i.jpg", imageCount);

            // open image file
            outputFile = fopen(image, "w");
            if (outputFile == NULL)
            {
                printf("Could not open %s.\n", image);
                return 3;
            }

            // increment number of image files created
            imageCount++;
        }

        // write to image file only if one exists
        if (outputFile != NULL)
        {
            // write to image file
            fwrite(buffer, sizeof(buffer), 1, outputFile);
        }

    }

    // close last image file
    fclose(outputFile);

    // close card.raw
    fclose(inputReady);

    // that's all folks
    return 0;
}

// Find the beginning of an jpg
bool isHeaderJPG(uint8_t buffer_header[])
{
    return buffer_header[0] == 0xff && buffer_header[1] == 0xd8 && buffer_header[2] == 0xff && (buffer_header[3] & 0xf0) == 0xe0;
}