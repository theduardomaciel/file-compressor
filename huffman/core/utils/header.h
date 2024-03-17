#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifndef HEADER_H
#define HEADER_H

typedef struct header_data
{
    uint16_t trash_size;
    uint16_t tree_size;
    uint64_t file_size;
    uint8_t *tree;
} header_data;

/**
 * @brief Inicializa o cabeçalho.
 *
 * @param file O arquivo onde o cabeçalho será escrito.
 */
void header_init(FILE *file);

/**
 * @brief Função de callback para escrever a árvore no cabeçalho.
 *
 * @param data Os dados a serem escritos.
 * @param arg O argumento adicional (opcional).
 */
void write_tree_callback(void *data, void *arg);

/**
 * @brief Escreve o cabeçalho no arquivo.
 *
 * @param file O arquivo onde o cabeçalho será escrito.
 * @param header Os dados do cabeçalho a serem escritos.
 */
void header_write(FILE *file, header_data *header);

/**
 * @brief Lê o cabeçalho do arquivo.
 *
 * @param file O arquivo de onde o cabeçalho será lido.
 * @return Os dados do cabeçalho lidos.
 */
header_data *header_read(FILE *file);

#endif // HEADER_H