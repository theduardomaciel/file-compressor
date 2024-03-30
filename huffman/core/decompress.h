#include "file_io.h"
#include "header.h"
#include "utils.h"

#include "huffman_tree.h"

#ifndef DECOMPRESS_H
#define DECOMPRESS_H

/**
 * Descomprime o arquivo de entrada e salva o resultado no caminho de saída especificado.
 *
 * @param input O ponteiro para o arquivo de entrada a ser descomprimido.
 * @param output_path O caminho para o arquivo de saída onde o resultado será salvo.
 */
void decompress(FILE *input, char *output_path);

void write_original_bytes(FILE *output_file, huffman_node *tree, huffman_node **current_node, uint8_t byte, uint8_t end_bit);

#endif // DECOMPRESS_H