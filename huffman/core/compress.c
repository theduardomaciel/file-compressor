#include "main.h"

#include "hash_table.h"
#include "priority_queue.h"
#include "frequency_table.h"

void DEBUG_tree(huffman_node *tree);

void print_byte_compressed_pairs(hash_table *table)
{
    printf("Byte Original\tByte Comprimido\n");
    printf("---------------------------------\n");
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (table->entries[i].original_byte != 0 || table->entries[i].compressed_byte != 0)
        {
            printf("%i\t\t%u\n", i, table->entries[i].compressed_byte);
        }
    }
}

void compress(FILE *input, char *output_path)
{
    // Construímos a tabela de frequências com base no arquivo de entrada
    uint64_t *frequency_table = build_frequency_table(input);

    // Construímos a fila de prioridade com base na tabela de frequências
    priority_queue *frequency_queue = build_frequency_queue(frequency_table);

    // Construímos a árvore de Huffman com base na fila de prioridade
    huffman_node *tree = build_huffman_tree(frequency_queue);
    //  DEBUG_tree(tree);

    // Construímos o dicionário que armazena os bytes comprimidos em seus respectivos bytes originais
    hash_table *bytes_dictionary = hash_table_init();

    // Construímos o dicionário de bytes com base na árvore de Huffman
    uint8_t *code = malloc(sizeof(uint8_t) * MAX_SIZE);
    build_bytes_dictionary(tree, bytes_dictionary, code, 0);

    print_byte_compressed_pairs(bytes_dictionary);

    free(code);

    // Criamos o arquivo de saída agora, a fim de evitar o gasto de recursos caso nos deparemos com algum erro durante a compressão
    FILE *output_file = open_file(output_path, "wb");

    // Realizamos a escrita do cabeçalho do arquivo de saída

    // Header - passo 1. Inicializamos o cabeçalho do arquivo
    header_init(output_file);

    // Header - passo 2. Escrevemos a árvore de Huffman após os 2 bytes reservados para o tamanho do lixo e da árvore
    ht_pre_order(tree, output_file);

    // Realizamos a escrita dos novos bytes comprimidos no arquivo de saída
    uint8_t current_byte;
    int8_t current_byte_index = 7;

    // Para isso, criamos uma variável que armazena o byte que será escrito no arquivo enquanto percorremos o dicionário
    uint8_t new_byte = 0;

    while (fread(&current_byte, sizeof(uint8_t), 1, input) == 1)
    {
        printf("current byte: %u\n", current_byte);
        printf("teste: %u\n", hash_table_get(bytes_dictionary, current_byte));
        // Itera por cada bit do byte utilizando operações bit a bit
        for (int i = 7; i >= 0; i--)
        {
            uint8_t bit_value = (hash_table_get(bytes_dictionary, current_byte) >> i) & 0x01;
            printf("%u", bit_value); // Exemplo de operação com o bit (impressão para demonstração)
        }
        printf("\n");
    }

    // Cada byte do arquivo
    /*  while (fread(&current_byte, sizeof(uint8_t), 1, input) == 1)
     {
         stack_node *current = bytes_dictionary[current_byte]->top;

         // Cada bit (8 bits) do arquivo
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
     } */

    // Checamos se a quantidade de bits do último byte é menor que 8
    // Se for, temos lixo e precisamos escrever o último byte no arquivo
    if (current_byte_index < 7)
    {
        fwrite(&new_byte, sizeof(uint8_t), 1, output_file);
    }

    // Header - passo 3. Calculamos o tamanho do lixo e o tamanho da árvore de Huffman e sobrescrevemos os placeholders no cabeçalho
    header_data *header = malloc(sizeof(header_data));

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