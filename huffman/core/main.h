#include <stdio.h>
#include <stdlib.h>

#include "huffman_tree.h"

#include "file_io.h"
#include "header.h"
#include "utils.h"

#ifndef MAIN_H
#define MAIN_H

/**
 * Comprime o conteúdo de um arquivo de entrada e salva o resultado em um arquivo de saída.
 *
 * @param input O ponteiro para o arquivo de entrada.
 * @param output_path O caminho para o arquivo de saída.
 */
void compress(FILE *input, char *output_path);

/**
 * Descomprime o arquivo de entrada e salva o resultado no caminho de saída especificado.
 *
 * @param input O ponteiro para o arquivo de entrada a ser descomprimido.
 * @param output_path O caminho para o arquivo de saída onde o resultado será salvo.
 */
void decompress(FILE *input, char *output_path);

#endif // MAIN_H