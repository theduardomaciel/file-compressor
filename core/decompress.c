#include <stdlib.h>
#include <stdio.h>

void decompress(char *input)
{
    FILE *input_file = open_file(input, "rb");
    FILE *output_file = open_file("decompressed", "w");

    printf("Descomprimindo arquivo %s para decompressed...\n", input);
}