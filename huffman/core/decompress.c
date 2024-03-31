#include "decompress.h"

void decompress(FILE *input, header_data *header, char *output_path)
{
    // DEBUG: Lemos o cabeçalho (header) do arquivo comprimido
    /* printf("🗃️  Componentes do header: \n");
    printf("-------------------------\n");
    printf("🗑️  Tamanho do lixo: %d\n", header->trash_size);
    printf("📏🌳 Tamanho da árvore: %d\n", header->tree_size);
    // printf("🌳 Árvore em pré-ordem: %s\n", header->preorder_tree);
    printf("📁 Tamanho da extensão: %lu\n", strlen(header->extension));
    printf("📚 Extensão: %s\n", header->extension);
    printf("🤏 Tamanho dos bytes comprimidos: %ld\n", header->file_size);
    printf("-------------------------\n"); */

    // 1. Construímos a árvore de Huffman com base na árvore em pré-ordem presente no cabeçalho
    huffman_node *tree = rebuild_huffman_tree(&header->preorder_tree);
    NULL_POINTER_CHECK(tree);
    // print_pre_order(tree);
    // print_tree_visually(tree, 0, '-');

    // 2. Criamos o arquivo descomprimido
    FILE *output_file = open_file(output_path, "wb");

    // 3. Realizamos a leitura dos novos bytes descomprimidos no arquivo de saída
    huffman_node *current_node = tree; // criamos uma variável para percorrer a árvore de Huffman
    uint8_t current_byte;

    // 3.1 Lemos os bytes comprimidos no arquivo, exceto o último, que pode conter lixo
    for (uint64_t byte_index = 0; byte_index < header->file_size - 1; byte_index++)
    {
        fread(&current_byte, sizeof(uint8_t), 1, input);

        write_original_bytes(output_file, tree, &current_node, current_byte, 0);
    }

    // 3.2 Caso o arquivo tenha lixo, lemos o último byte
    if (header->trash_size > 0)
    {
        fread(&current_byte, sizeof(uint8_t), 1, input);

        // Como o último byte pode conter bits que não fazem parte do arquivo original, o lixo, não podemos ler todos os 8 bits
        // Portanto, enviamos o tamanho do lixo como argumento para que a função saiba quantos bits deve ler
        write_original_bytes(output_file, tree, &current_node, current_byte, header->trash_size);
    }

    // 4. Fechamos o arquivo de saída
    fclose(output_file);
}

/*
    Aqui, para não ter que retornar o nó atual a cada leitura de byte, passamos o endereço do nó atual como argumento
    e atualizamos o nó atual conforme percorremos a árvore de Huffman

    Dessa forma, podemos ler os bytes do arquivo de entrada e escrever os bytes originais no arquivo de saída,
    sem precisar atualizar o valor de current_node na função principal após cada leitura de byte

    Uma versão alternativa está presente comentada abaixo da função "write_original_bytes"
*/

void write_original_bytes(FILE *output_file, huffman_node *tree, huffman_node **current_node, uint8_t byte, uint8_t end_bit)
{
    // Para cada bit do byte lido, percorremos a árvore de Huffman
    for (int j = 7; j >= end_bit; j--)
    {
        // Se o bit j do byte for 1, percorremos a árvore para a direita, caso contrário, percorremos para a esquerda
        if (is_bit_i_set(byte, j))
        {
            *current_node = (*current_node)->right;
        }
        else
        {
            *current_node = (*current_node)->left;
        }

        // Se chegarmos a uma folha, escrevemos o caractere no arquivo de saída e voltamos para a raiz da árvore
        if (is_leaf(*current_node))
        {
            fwrite((*current_node)->data, sizeof(uint8_t), 1, output_file);
            *current_node = tree; // voltamos para a raiz da árvore
        }
    }
}

/*
    Como alternativa, poderíamos utilizar a seguinte abordagem, na qual a função write_original_bytes retorna o nó atual da árvore de Huffman
    Na função compress faríamos o seguinte:

    ```c
    huffman_node *current_node = tree; // criamos uma variável para percorrer a árvore de Huffman
    uint8_t current_byte;

    // 3.1 Lemos os bytes comprimidos no arquivo, exceto o último, que pode conter lixo
    for (uint64_t byte_index = 0; byte_index < header->file_size - 1; byte_index++)
    {
        fread(&current_byte, sizeof(uint8_t), 1, input);

        current_node = write_original_bytes(output_file, tree, current_node, current_byte, 0);
    }
    ```

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
*/