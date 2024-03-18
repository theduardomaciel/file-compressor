#include "main.h"

#include "file_io.h"
#include "header.h"
#include "utils.h"

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
    uint8_t current_byte;

    // Lemos os bytes do arquivo de entrada, exceto o último, que pode conter lixo
    for (uint64_t byte_index = 0; byte_index < bytes_to_read - 1; byte_index++)
    {
        fread(&current_byte, sizeof(uint8_t), 1, input);

        // Para cada bit do byte lido, percorremos a árvore de Huffman
        for (int j = 7; j >= 0; j--)
        {
            // Se o bit j do byte for 1, percorremos a árvore para a direita, caso contrário, percorremos para a esquerda
            if (is_bit_i_set(current_byte, j))
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

    // Lemos o último byte do arquivo de entrada, até o tamanho do lixo, caso ele exista
    if (file_header->trash_size > 0)
    {
        fread(&current_byte, sizeof(uint8_t), 1, input);

        for (int j = 7; j >= file_header->trash_size; j--)
        {
            if (is_bit_i_set(current_byte, j))
            {
                current_node = current_node->right;
            }
            else
            {
                current_node = current_node->left;
            }

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
