#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "compression.h"

#include "utils.h"
#include "file_io.h"
#include "header.h"

#include "huffman_tree.h"

huffman_node *rebuild_huffman_tree(uint8_t **header_tree);

void decompress(FILE *input, char *output_path)
{
    // Lemos o cabeçalho do arquivo de entrada
    header_data *file_header = header_read(input);

    printf("Tamanho do lixo: %d\n", file_header->trash_size);
    printf("Tamanho da árvore: %d\n", file_header->tree_size);
    printf("Tamanho do header: %lu\n", file_header->tree_size + sizeof(uint16_t));

    // Construímos a árvore de Huffman com base na árvore lida do arquivo de entrada
    huffman_node *tree = rebuild_huffman_tree(&file_header->tree);
    NULL_POINTER_CHECK(tree);

    // print_pre_order(tree);
    // print_tree_visually(tree, 0, '-');

    // Criamos o arquivo de saída agora, a fim de evitar o gasto de recursos caso nos deparemos com algum erro durante a descompressão
    FILE *output_file = open_file(output_path, "wb");

    uint64_t bytes_to_read = file_header->file_size - (file_header->tree_size + sizeof(uint16_t));
    printf("Tamanho do arquivo comprimido: %lu\n", file_header->file_size);
    printf("Bytes para ler: %lu\n", bytes_to_read);

    // Realizamos a leitura dos novos bytes descomprimidos no arquivo de saída
    huffman_node *current_node = tree;
    uint8_t byte;

    for (uint64_t i = 0; i < bytes_to_read; i++)
    {
        fread(&byte, sizeof(uint8_t), 1, input);

        // Para cada bit do byte lido, percorremos a árvore de Huffman
        for (int j = 7; j >= 0; j--)
        {
            // Se o bit j do byte for 1, percorremos a árvore para a direita, caso contrário, percorremos para a esquerda
            if (is_bit_i_set(byte, j))
            {
                current_node = current_node->right;
            }
            else
            {
                current_node = current_node->left;
            }

            // Se chegamos a uma folha, escrevemos o caractere no arquivo de saída e voltamos para a raiz da árvore
            if (is_leaf(current_node))
            {
                fwrite(current_node->data, sizeof(uint8_t), 1, output_file);
                current_node = tree;
            }
        }
    }

    // Fechamos os arquivos de saída
    fclose(output_file);
}

// Nós internos sempre serão representados por um *, no entanto, para diferenciá-lo de uma folha, precisamos 'escapar' o caractere
// Para isso, utilizamos o caractere '\' antes do '*', indicando que o próximo caractere representa uma folha
huffman_node *rebuild_huffman_tree(uint8_t **header_tree)
{
    // Alocamos espaço para armazenar o símbolo atual da árvore
    uint8_t *item = malloc(sizeof(uint8_t));
    uint8_t *current_symbol = *header_tree; // Obtém o símbolo atual da árvore

    // Obs.: Ao utilizar (*header_tree)++ estamos avançando para o próximo símbolo

    // Se o símbolo atual for '*', indica um nó interno
    if (*current_symbol == '*')
    {
        *item = '*';
        (*header_tree)++;

        // Reconstruímos as subárvores esquerda e direita recursivamente
        huffman_node *left = rebuild_huffman_tree(header_tree);
        huffman_node *right = rebuild_huffman_tree(header_tree);

        // Criamos um nó com as subárvores esquerda e direita
        return ht_create_node((void *)item, 0, left, right);
    }
    else
    {
        // Se o símbolo atual for '\', indica que o próximo símbolo é um caractere especial,
        // portanto, avançamos para o próximo símbolo e o armazenamos em item
        if (*current_symbol == '\\')
        {
            (*header_tree)++;
            *item = **header_tree;
            (*header_tree)++;
        }
        else
        {
            // Caso contrário, o símbolo atual é um caractere normal, então o armazenamos em item e avançamos para o próximo símbolo
            *item = *current_symbol;
            (*header_tree)++;
        }

        // Criamos e retornamos um nó da árvore de Huffman com o símbolo atual
        huffman_node *node = ht_create_node((void *)item, 0, NULL, NULL);
        return node;
    }
}
