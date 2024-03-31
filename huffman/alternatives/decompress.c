#include "file_io.h"
#include "header.h"
#include "utils.h"

#include "huffman_tree.h"

/*
    Nessa abordagem, não utilizamos um ponteiro duplo para o nó atual da árvore de Huffman.
    Em vez disso, retornamos o nó atual após a leitura do byte, para que possamos atualizar
    o nó atual na função principal.

    Portanto, a função "write_original_bytes" deixa de retornar void e passa a retornar
    um ponteiro huffman_node* que representa o último nó explorado na árvore de Huffman.
*/

void decompress(FILE *input, char *output_path)
{
    // 1. Lemos o cabeçalho (header) do arquivo comprimido
    header_data *file_header = header_read(input);

    printf("🗃️  Tamanho do header: %ld + %d = %lu\n", sizeof(uint16_t), file_header->tree_size, sizeof(uint16_t) + file_header->tree_size);

    // 2. Construímos a árvore de Huffman com base na árvore em pré-ordem presente no cabeçalho
    huffman_node *tree = rebuild_huffman_tree(&file_header->preorder_tree);
    NULL_POINTER_CHECK(tree);
    // print_pre_order(tree);
    // print_tree_visually(tree, 0, '-');

    // 3. Criamos o arquivo descomprimido
    FILE *output_file = open_file(output_path, "wb");

    // 4. Calculamos o tamanho do arquivo original
    uint64_t bytes_to_read = file_header->file_size - (sizeof(uint16_t) + file_header->tree_size);
    /*
        O tamanho do arquivo original é igual ao tamanho do arquivo comprimido menos o tamanho do cabeçalho,
        adicionado no arquivo comprimido para que possamos reconstruir o arquivo original

        O tamanho do cabeçalho é igual ao:
            [tamanho do lixo + tamanho da árvore em pré-ordem] (2 bytes) + [árvore em pré-ordem]

        Portanto, o tamanho do arquivo original é igual ao :
            [tamanho do arquivo comprimido] - [tamanho do cabeçalho]
    */

    printf("📁 Tamanho total do arquivo comprimido: %lu (%lu bytes de dados)\n", file_header->file_size, bytes_to_read);

    // 5. Realizamos a leitura dos novos bytes descomprimidos no arquivo de saída
    huffman_node *current_node = tree; // criamos uma variável para percorrer a árvore de Huffman
    uint8_t current_byte;

    // 5.1 Lemos os bytes do arquivo de entrada, exceto o último, que pode conter lixo
    for (uint64_t byte_index = 0; byte_index < bytes_to_read - 1; byte_index++)
    {
        fread(&current_byte, sizeof(uint8_t), 1, input);

        current_node = write_original_bytes(output_file, tree, current_node, current_byte, 0);
    }

    // 5.2 Caso o arquivo tenha lixo, lemos o último byte
    if (file_header->trash_size > 0)
    {
        fread(&current_byte, sizeof(uint8_t), 1, input);

        // Como o último byte pode conter bits que não fazem parte do arquivo original, o lixo, não podemos ler todos os 8 bits
        // Portanto, enviamos o tamanho do lixo como argumento para que a função saiba quantos bits deve ler
        write_original_bytes(output_file, tree, current_node, current_byte, file_header->trash_size);
    }

    // 6. Fechamos o arquivo de saída
    fclose(output_file);
}

huffman_node *write_original_bytes(FILE *output_file, huffman_node *tree, huffman_node *current_node, uint8_t byte, uint8_t end_bit)
{
    // Para cada bit do byte lido, percorremos a árvore de Huffman
    for (int j = 7; j >= end_bit; j--)
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

        // Se chegarmos a uma folha, escrevemos o caractere no arquivo de saída e voltamos para a raiz da árvore
        if (is_leaf(*current_node))
        {
            fwrite((uint8_t *)current_node->data, sizeof(uint8_t), 1, output_file);
            current_node = tree; // voltamos para a raiz da árvore
        }
    }

    return current_node;
}