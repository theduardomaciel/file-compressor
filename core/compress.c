#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compress.h"

#include "file_io.h"
#include "heap.h"
#include "huffman_tree.h"
#include "frequency_table.h"

void compress(char *input)
{
    FILE *input_file = open_file(input, "r");
    FILE *output_file = open_file("compressed", "wb");

    char *output_name = extract_filename(input);

    printf("Comprimindo arquivo %s para %s...\n", input, output_name);

    char *content = read_file(input_file);

    // Criação da tabela de frequência
    unsigned *freq = new_frequency_table(content);
}