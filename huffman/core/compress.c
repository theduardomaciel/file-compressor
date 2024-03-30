#include "main.h"

#include "priority_queue.h"
#include "frequency_table.h"
#include "bytes_dictionary.h"

void DEBUG_tree(huffman_node *tree);

uint8_t compress_bytes(FILE *input_file, FILE *output_file, byte_path *paths)
{
    // Para isso, precisamos percorrer o arquivo de entrada byte a byte e, para cada byte, percorrer o dicionário para obter o caminho correspondente
    uint8_t current_byte;
    int8_t current_byte_index = 7;

    // Criamos uma variável que armazena o byte que será escrito no arquivo enquanto percorremos o dicionário
    uint8_t new_byte = 0;

    // Percorremos cada byte do arquivo
    while (fread(&current_byte, sizeof(uint8_t), 1, input_file) == 1)
    {
        byte_path current = paths[current_byte];

        // Percorremos cada bit (8 no total) do byte atual
        for (int i = 0; i < current.path_length; i++)
        {
            // Se o bit atual é 1, setamos o bit correspondente no novo byte
            if (current.path[i] == 1)
            {
                new_byte = set_bit(new_byte, current_byte_index);
            }

            // Avançamos para o próximo bit do novo byte (da direita para a esquerda)
            current_byte_index--;

            // Se o byte está completo, escrevemos ele no arquivo
            if (current_byte_index < 0)
            {
                fwrite(&new_byte, sizeof(uint8_t), 1, output_file);
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
    }

    // Calculamos o tamanho do lixo (quantidade de bits que não foram preenchidos no último byte)
    return current_byte_index;
}

void compress(FILE *input_file, char *output_path)
{
    // 1. Construímos a tabela de frequências com base no arquivo de entrada
    uint64_t *frequency_table = build_frequency_table(input_file);

    // 2. Construímos a fila de prioridade com base na tabela de frequências
    priority_queue *frequency_queue = build_frequency_queue(frequency_table);

    // 3. Construímos a árvore de Huffman com base na fila de prioridade
    huffman_node *tree = build_huffman_tree(frequency_queue);
    // DEBUG_tree(tree);

    // 4. Construímos o dicionário que armazena os bytes comprimidos em seus respectivos bytes originais

    byte_path paths[256] = {0}; // Array de byte_path's para armazenar os caminhos de cada byte na árvore de Huffman
    uint8_t current_path[256];  // Array para armazenar o caminho atual durante a recursão

    // Chamada da função para gerar os caminhos de cada byte na árvore de Huffman
    build_bytes_dictionary(tree, paths, current_path, 0);
    // DEBUG_dictionary(paths);

    // 5. Criamos o arquivo de saída
    FILE *output_file = open_file(output_path, "wb");

    // 6. Realizamos a escrita do cabeçalho (header) do arquivo comprimido

    // 6.1. Inicializamos o cabeçalho do arquivo reservando 2 bytes para o:
    // ➡ tamanho do lixo (3 bits)
    // ➡ tamanho da árvore em pré-ordem (13 bits)
    header_data *header = header_init(output_file);

    // 6.2. Escrevemos a árvore de Huffman no arquivo após os 2 bytes reservados
    ht_write_pre_order(tree, output_file);

    // 6.3. Escrevemos os bytes comprimidos (obtidos com base no dicionário) no arquivo
    uint8_t current_byte_index = compress_bytes(input_file, output_file, paths);

    // 6.4. Sobrescrevemos os placeholders (2 bytes) que declaramos anteriormente

    // Para isso, calculamos o tamanho do lixo e o tamanho da árvore em pré-ordem

    header->tree_size = ht_get_tree_size(tree);

    // Obtemos o tamanho do lixo obtendo a posição do último bit escrito no arquivo (somamos 1 para isso)
    // e realizando o bit shift para esquerda de 13, equivalente à quantidade de bits ocupada pelo tamanho da árvore
    header->trash_size = (current_byte_index + 1) << 13;

    printf("🌳 Tamanho da árvore: %d\n", header->tree_size);
    printf("🗑️  Tamanho do lixo: %d\n", *(uint16_t *)&header->trash_size >> 13);
    // printf("Posição do bite atual: %d\n", current_byte_index);

    // Preenchemos os espaços reservados no cabeçalho para o tamanho do lixo e da árvore de Huffman
    header_write(output_file, header);

    close_file(output_file);
}

void DEBUG_tree(huffman_node *tree)
{
    print_pre_order(tree);
    print_tree_visually(tree, 0, '-');
}