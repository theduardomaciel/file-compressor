#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "string.h"

#ifndef HEADER_H
#define HEADER_H

typedef struct header_data
{
    char *extension;
    size_t file_size;
    uint16_t trash_size;
    uint16_t tree_size; // Tamanho da árvore em pré-ordem
    uint8_t *preorder_tree;
    /*
        O tamanho da árvore de Huffman é variável, então o número de bytes necessários para armazená-la também é variável.
        Portanto, a árvore é armazenada como um array de bytes.
        Também é possível representar a árvore em pré-ordem como: uint8_t preorder_tree[tree_size]
    */
} header_data;

/**
 * @brief Inicializa o cabeçalho.
 *
 * @return header_data A struct do header inicializada.
 */
header_data *header_init();

/**
 * @brief Reserva espaço para o cabeçalho no arquivo.
 *
 * @param file O arquivo onde o espaço será reservado.
 */
void header_reserve_space(FILE *file);

/**
 * @brief Escreve o cabeçalho no arquivo.
 *
 * @param file O arquivo onde o cabeçalho será escrito.
 * @param header Os dados do cabeçalho a serem escritos.
 */
void header_write_to_file(FILE *file, header_data *header);

/**
 * @brief Lê o cabeçalho do arquivo.
 *
 * @param file O arquivo de onde o cabeçalho será lido.
 * @return Os dados do cabeçalho lidos.
 */
header_data *header_read(FILE *file);

/**
 * @brief Lê a extensão do arquivo armazenada no cabeçalho.
 *
 * @param file O arquivo de onde a extensão será lida.
 * @return A extensão do arquivo lida.
 */
char *header_read_extension(FILE *file);

#endif // HEADER_H