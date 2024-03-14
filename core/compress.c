#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compress.h"

#include "file_io.h"
#include "utils.h"

#include "huffman_tree.h"
#include "frequency_table.h"

#define MAX_BUFFER_SIZE 1000000
#define MAX_POSSIBLE_BYTE_VALUE 256

void compress(char *input)
{
    FILE *input_file = open_file(concat_strings("./input/", input), "r");
    // FILE *output_file = open_file("compressed", "wb");

    printf("🤏 Comprimindo arquivo `%s` para `%s`...\n\n", input, concat_strings(extract_filename(input), ".huff"));

    char *data = read_file(input_file);
    int *frequency = new_frequency_table(data);

    create_huffman_tree(frequency);
}