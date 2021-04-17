// Modifies the volume of an audio file
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments // Verifique os argumentos da linha de comando
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor // Abra arquivos e determine o fator de escala

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

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file // TODO: Copia o cabeçalho do arquivo de entrada para o arquivo de saída
    uint8_t header[HEADER_SIZE];
    fread(header, HEADER_SIZE, 1, input);
    fwrite(header, HEADER_SIZE, 1, output);

    // TODO: Read samples from input file and write updated data to output file // TODO: Ler amostras do arquivo de entrada e gravar dados atualizados no arquivo de saída
    int16_t BUFFER = 0;
    while (fread(&BUFFER, 2, 1, input))
    {
        BUFFER = BUFFER * factor;
        fwrite(&BUFFER, 2, 1, output);
    }

    // Close files // Fecha os arquivos
    fclose(input);
    fclose(output);
}
