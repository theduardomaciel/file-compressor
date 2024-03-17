#include "main.h"

#include "file_io.h"
#include "header.h"
#include "utils.h"

#include "frequency_table.h"
#include "priority_queue.h"
#include "huffman_tree.h"

void DEBUG_tree(huffman_node *tree);

void DEBUG_dictionary(stack *dictionary[MAX_SIZE]);

void compress(FILE *input, char *output_path)
{
    // Construímos a tabela de frequências com base no arquivo de entrada
    uint64_t *frequency_table = build_frequency_table(input);

    // Construímos a fila de prioridade com base na tabela de frequências
    priority_queue *frequency_queue = build_frequency_queue(frequency_table);

    // Construímos a árvore de Huffman com base na fila de prioridade
    huffman_node *tree = build_huffman_tree(frequency_queue);
    // print_pre_order(tree);
    //  DEBUG_tree(tree);

    // Construímos o dicionário que armazena os bytes comprimidos em seus respectivos bytes originais
    stack *current_path = stack_init();
    stack **bytes_dictionary = malloc(MAX_SIZE * sizeof(stack *));
    memset(bytes_dictionary, 0, MAX_SIZE * sizeof(stack *));

    build_bytes_dictionary(tree, bytes_dictionary, current_path);
    free(current_path);
    // DEBUG_dictionary(bytes_dictionary);

    // Criamos o arquivo de saída agora, a fim de evitar o gasto de recursos caso nos deparemos com algum erro durante a compressão
    FILE *output_file = open_file(output_path, "wb");

    // Realizamos a escrita do cabeçalho do arquivo de saída

    // Header - passo 1. Inicializamos o cabeçalho do arquivo
    header_init(output_file);

    // Header - passo 2. Escrevemos a árvore de Huffman após os 2 bytes reservados para o tamanho do lixo e da árvore
    ht_pre_order(tree, write_tree_callback, output_file);

    // Realizamos a escrita dos novos bytes comprimidos no arquivo de saída
    uint8_t current_byte;
    int8_t current_byte_index = 7;

    // Para isso, criamos uma variável que armazena o byte que será escrito no arquivo enquanto percorremos o dicionário
    uint8_t new_byte = 0;

    while (fread(&current_byte, sizeof(uint8_t), 1, input) == 1)
    {
        stack_node *current = bytes_dictionary[current_byte]->top;

        while (current != NULL)
        {
            // Como o novo byte é inicializado com 0, somente nos preocupamos em setar os bits 1s
            if (*(uint8_t *)current->data == 1)
            {
                new_byte = set_bit(new_byte, current_byte_index);
            }

            // Caso cheguemos ao final do byte, escrevemos o byte no arquivo e, em seguida,
            // re-setamos a variável que armazena o novo byte e o índice atual para repetir o processo com o próximo byte
            if (--current_byte_index < 0)
            {
                fwrite(&new_byte, sizeof(uint8_t), 1, output_file);

                new_byte = 0;
                current_byte_index = 7;
            }

            current = current->next;
        }
    }

    // Checamos se a quantidade de bits do último byte é menor que 8
    // Se for, temos lixo e precisamos escrever o último byte no arquivo
    if (current_byte_index < 7)
    {
        fwrite(&new_byte, sizeof(uint8_t), 1, output_file);
    }

    // Header - passo 3. Calculamos o tamanho do lixo e o tamanho da árvore de Huffman e sobrescrevemos os placeholders no cabeçalho
    header_data *header = malloc(sizeof(header_data));

    header->tree_size = ht_get_tree_size(tree);
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

void DEBUG_dictionary(stack *dictionary[MAX_SIZE])
{
    printf("Dicionário de bytes:\n");
    print_dictionary(dictionary);
}

/*
    // Cálculo do número total de bits necessários para representar os nós internos da árvore
    int num_bits_tree = (1 << (huffman_tree_height + 1)) - 1; // Fórmula para uma árvore binária completa

    // Cálculo do número total de bits na árvore (incluindo folhas)
    int num_bits_total = num_bits_tree + num_folhas;

    // Cálculo do número de bits de lixo
    int num_bits_trash = 8 - (num_bits_total % 8);
*/