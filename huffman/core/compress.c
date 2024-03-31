#include "compress.h"

void compress(FILE *input_file, char *output_path)
{
    // 1. Construímos a tabela de frequências com base no arquivo de entrada
    uint64_t *frequency_table = build_frequency_table(input_file);

    // 2. Construímos a fila de prioridade com base na tabela de frequências
    priority_queue *frequency_queue = build_frequency_queue(frequency_table);

    // 3. Construímos a árvore de Huffman com base na fila de prioridade
    huffman_node *tree = build_huffman_tree(frequency_queue);
    // print_pre_order(tree);
    // print_tree_visually(tree, 0, '-');

    // 4. Construímos o dicionário que armazena os bytes comprimidos em seus respectivos bytes originais

    byte_path paths[256] = {0}; // Array de byte_path's para armazenar os caminhos de cada byte na árvore de Huffman
    uint8_t current_path[256];  // Array para armazenar o caminho atual durante a recursão

    // Chamada da função para gerar os caminhos de cada byte na árvore de Huffman
    build_bytes_dictionary(tree, paths, current_path, 0);
    // DEBUG_dictionary(paths);

    // 5. Criamos o arquivo de saída
    FILE *output_file = open_file(output_path, "wb");

    // 6. Realizamos a escrita do cabeçalho (header) do arquivo comprimido

    // 6.1 Antes de realizarmos outras escritas no arquivo, reservamos 2 bytes para o:
    // ➡ tamanho do lixo (3 bits)
    // ➡ tamanho da árvore em pré-ordem (13 bits)
    header_reserve_space(output_file);

    // 6.2 Escrevemos a árvore de Huffman no arquivo após os 2 bytes reservados
    ht_write_pre_order(tree, output_file);

    // 6.3 Escrevemos os bytes comprimidos (obtidos com base no dicionário) no arquivo
    int trash_size = write_compressed_bytes(input_file, output_file, paths);

    // 6.4 Sobrescrevemos o espaço reservado no arquivo (2 bytes) anteriormente com os dados reais
    header_data *header = header_init();

    // 6.4.1 Para isso, inserimos o tamanho do lixo (quantidade de bits que não foram preenchidos no último byte)
    header->trash_size = trash_size << 13;
    /*
        Realizamos um shift de 13 bits para a esquerda pois o tamanho do lixo
        ocupa os 3 primeiros bits do primeiro byte do cabeçalho:
        16 bits (2 bytes) - 3 bits (tamanho do lixo) = 13 bits
    */

    // 6.4.2 E o tamanho da árvore de Huffman em pré-ordem
    header->tree_size = ht_get_tree_size(tree);

    printf("🗑️  Tamanho do lixo: %d\n", trash_size);
    printf("🌳 Tamanho da árvore: %d\n", header->tree_size);

    // 6.4.3 Preenchemos os espaços reservados no cabeçalho (header) do arquivo
    header_write_to_file(output_file, header);

    close_file(output_file);
}

void DEBUG_print_byte(uint8_t byte)
{
    for (int i = 7; i >= 0; i--)
    {
        printf("%d", byte >> i & 1);
    }
    printf(" ");
}

void DEBUG_print_byte_with_trash(uint8_t byte, int current_byte_index)
{
    printf("[");
    for (int i = 7; i >= 0; i--)
    {
        if (i == current_byte_index)
        {
            printf("-");
        }
        printf("%d", byte >> i & 1);
    }
    printf("] (último byte com lixo)");
    printf("\n");
}

uint8_t write_compressed_bytes(FILE *input_file, FILE *output_file, byte_path *paths)
{
    // Para isso, precisamos percorrer o arquivo de entrada byte a byte e, para cada byte, percorrer o dicionário para obter o caminho correspondente
    uint8_t current_byte;
    int8_t current_byte_index = 7;

    // Criamos uma variável que armazena o byte que será escrito no arquivo enquanto percorremos o dicionário
    uint8_t new_byte = 0;

    // Percorremos cada byte do arquivo
    // printf("Bytes escritos no arquivo:\n");
    while (fread(&current_byte, sizeof(uint8_t), 1, input_file) == 1)
    {
        byte_path current = paths[current_byte];

        // Percorremos cada bit (8 no total) do byte atual
        for (int i = 0; i < current.path_length; i++)
        {
            // Se o bit atual é 1, setamos o bit correspondente no novo byte
            if (current.path[i] == 1)
            {
                /*
                    Inicializamos o current_byte_index com 7 pois estamos percorrendo o byte da esquerda para a direita
                    Ao realizar operações com bits, caso queiramos setar o bit mais à esquerda, precisamos setar o bit 7
                    Exemplo:    00000001    (usamos como base o byte 1 em funções de bits)
                                1 << 7      (setamos o bit mais à esquerda)
                                10000000
                                =
                                10000000    (fazemos um OR bit a bit entre 10000000 e o new_byte atual = 00000000)
                                00000000
                                =
                                10000000    (o new_byte agora é 10000000)

                    Caso quiséssemos utilizar 0 como valor inicial, teríamos que passar (7 - current_byte_index) como argumento
                */
                new_byte = set_bit(new_byte, current_byte_index);
            }

            // Avançamos para o próximo bit do novo byte
            current_byte_index--;

            // Se o byte está completo, escrevemos ele no arquivo
            if (current_byte_index < 0)
            {
                fwrite(&new_byte, sizeof(uint8_t), 1, output_file);

                // Printamos o byte que acabamos de escrever
                // DEBUG_print_byte(new_byte);

                current_byte_index = 7;
                new_byte = 0;
            }
        }
    }

    // Checamos se o último byte não foi completado
    // Se não tiver sido completado, precisamos escrevê-lo no arquivo pois no loop somente escrevemos o byte quando ele está completo
    if (current_byte_index < 7)
    {
        fwrite(&new_byte, sizeof(uint8_t), 1, output_file);

        // DEBUG_print_byte_with_trash(new_byte, current_byte_index);
    }

    printf("📦 Bytes comprimidos escritos no arquivo!\n");

    /*
        Para retornarmos o tamanho do lixo corretamente, precisamos tomar cuidado com o fato de que estamos contando de 7 a 0.
        Caso estivéssemos contando de 0 a 7, poderíamos realizar: 8 - current_byte_index
        No entanto, como estamos contando de 7 a 0, precisamos realizar: current_byte_index + 1

        Exemplo:
        Caso o current_byte_index seja 3, um byte atual poderia ser: 1010[0000]
            -   Após a escrita de 1: current_byte_index-- = 7 - 1 = 6
            -   Após a escrita de 0: current_byte_index-- = 6 - 1 = 5
            -   Após a escrita de 1: current_byte_index-- = 5 - 1 = 4
            -   Após a escrita de 0: current_byte_index-- = 4 - 1 = 3
        Neste caso, o tamanho do lixo seria 4, pois faltam 4 bits para completar o byte
    */

    return current_byte_index + 1;
}