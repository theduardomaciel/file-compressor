#include "bytes_dictionary.h"

void build_bytes_dictionary(huffman_node *node, byte_path paths[MAX_SIZE], uint8_t current_path[], int depth)
{
    if (node == NULL)
    {
        return;
    }

    if (is_leaf(node))
    {
        // Se o nó atual é uma folha, armazena o caminho do byte no array de byte_path
        uint8_t leaf_byte = *(uint8_t *)node->data;
        paths[leaf_byte].path_length = depth;
        for (int i = 0; i < depth; i++)
        {
            paths[leaf_byte].path[i] = current_path[i];
        }
    }
    else
    {
        // Se o nó atual não é uma folha, continua a recursão para os nós filhos

        current_path[depth] = 0; // 0 indica caminho à esquerda
        build_bytes_dictionary(node->left, paths, current_path, depth + 1);

        current_path[depth] = 1; // 1 indica caminho à direita
        build_bytes_dictionary(node->right, paths, current_path, depth + 1);
    }
}

// ⮕ Funções de DEBUG

void DEBUG_dictionary(byte_path *dictionary)
{
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (dictionary[i].path_length > 0)
        {
            printf("Byte %d (%c): ", i, i);
            for (int j = 0; j < dictionary[i].path_length; j++)
            {
                printf("%d", dictionary[i].path[j]);
            }
            printf("\n");
        }
    }
}