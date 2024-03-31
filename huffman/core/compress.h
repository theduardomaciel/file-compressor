#include "file_io.h"
#include "header.h"
#include "utils.h"

#include "huffman_tree.h"
#include "priority_queue.h"
#include "frequency.h"
#include "bytes_dictionary.h"

#ifndef COMPRESS_H
#define COMPRESS_H

/**
 * @brief Comprime o conteúdo de um arquivo de entrada e salva o resultado em um arquivo de saída.
 *
 * @param input O ponteiro para o arquivo de entrada.
 * @param input_extension A extensão do arquivo de entrada.
 * @param output_path O caminho para o arquivo de saída.
 */
void compress(FILE *input_file, char *input_extension, char *output_path);

/**
 * @brief Escreve os bytes comprimidos no arquivo de saída.
 *
 * @param input O ponteiro para o arquivo de entrada.
 * @param output O ponteiro para o arquivo de saída.
 * @param paths O array de byte_path's que armazena os caminhos de cada byte na árvore de Huffman.
 * @return O índice do último byte escrito no arquivo de saída.
 */
uint8_t write_compressed_bytes(FILE *input, FILE *output, byte_path *paths);

#endif // COMPRESS_H