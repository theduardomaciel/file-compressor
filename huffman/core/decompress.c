#include "main.h"

#include "file_io.h"
#include "header.h"
#include "utils.h"

#include "huffman_tree.h"

typedef struct
{
    huffman_node *tree;
    huffman_node **current_node;
    FILE *output_file;
    uint8_t end_bit;
} BitProcessingState;

huffman_node *rebuild_huffman_tree(uint8_t **header_tree);

void process_byte(uint8_t byte, BitProcessingState *state);

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

    BitProcessingState state = {
        .current_node = &current_node,
        .output_file = output_file,
        .tree = tree,
        .end_bit = 0};

    // Lemos os bytes do arquivo de entrada, exceto o último, que pode conter lixo
    for (uint64_t byte_index = 0; byte_index < bytes_to_read - 1; byte_index++)
    {
        fread(&current_byte, sizeof(uint8_t), 1, input);

        process_byte(current_byte, &state);
        // process_byte(current_byte, &(BitProcessingState){tree, &current_node, output_file, 0});
    }

    // Lemos o último byte do arquivo de entrada, até o tamanho do lixo, caso ele exista
    if (file_header->trash_size > 0)
    {
        fread(&current_byte, sizeof(uint8_t), 1, input);

        // Determinamos o número de bits a serem lidos do último byte
        // Como o último byte pode conter lixo, não podemos ler todos os 8 bits
        state.end_bit = file_header->trash_size;

        process_byte(current_byte, &state);
        // process_byte(current_byte, &(BitProcessingState){tree, &current_node, output_file, file_header->trash_size});
    }

    // Fechamos os arquivos de saída
    fclose(output_file);
}

void process_byte(uint8_t byte, BitProcessingState *state)
{
    // Para cada bit do byte lido, percorremos a árvore de Huffman
    for (int j = 7; j >= state->end_bit; j--)
    {
        // Se o bit j do byte for 1, percorremos a árvore para a direita, caso contrário, percorremos para a esquerda
        if (is_bit_i_set(byte, j))
        {
            *(state->current_node) = (*(state->current_node))->right;
        }
        else
        {
            *(state->current_node) = (*(state->current_node))->left;
        }

        // Se chegarmos a uma folha, escrevemos o caractere no arquivo de saída e voltamos para a raiz da árvore
        if (is_leaf(*(state->current_node)))
        {
            fwrite((*(state->current_node))->data, sizeof(uint8_t), 1, state->output_file);
            *(state->current_node) = state->tree;
        }
    }
}
