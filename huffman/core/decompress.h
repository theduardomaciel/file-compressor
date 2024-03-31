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
 * @param header O cabeçalho do arquivo de entrada.
 * @param output_path O caminho para o arquivo de saída onde o resultado será salvo.
 */
void decompress(FILE *input, header_data *header, char *output_path);

/**
 * Descomprime os bytes, escrevendo os correspondentes originais no arquivo de saída.
 *
 * @param output_file O ponteiro para o arquivo de saída.
 * @param tree A árvore de Huffman.
 * @param current_node O endereço do nó atual na árvore de Huffman.
 * @param byte O byte a ser escrito.
 * @param end_bit Até que bit do byte devemos ler.
 */
void write_original_bytes(FILE *output_file, huffman_node *tree, huffman_node **current_node, uint8_t byte, uint8_t end_bit);

#endif // DECOMPRESS_H