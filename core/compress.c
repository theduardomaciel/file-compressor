#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compress.h"
#include "huffman_tree.h"

void compress(char *input, char *output)
{
    printf("Comprimindo arquivo %s para %s\n", input, output);

    // Cria a árvore de Huffman
    huffman_tree *tree = create_huffman_tree();
}