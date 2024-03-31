#include "utils.h"
#include "huffman_tree.h"

#ifndef BYTES_DICTIONARY_H
#define BYTES_DICTIONARY_H

// Estrutura para armazenar o caminho de um byte na árvore de Huffman
typedef struct byte_path
{
    uint8_t path[MAX_SIZE]; // Caminho do byte (0 ou 1)
    uint8_t path_length;    // Comprimento do caminho
} byte_path;

/**
 * @brief Função recursiva para gerar os caminhos de cada byte ao percorrer a árvore de Huffman
 *
 * @param node Nó atual da árvore de Huffman (começa na raiz)
 * @param paths Array de byte_path para armazenar os caminhos de cada byte
 * @param current_path Array para armazenar o caminho atual na recursão
 * @param depth Profundidade atual na árvore de Huffman (começa em 0)
 */
void build_bytes_dictionary(huffman_node *node, byte_path paths[MAX_SIZE], uint8_t current_path[], int depth);

/*
    ⮕ Declarações das funções de impressão
    São funções que imprimem elementos úteis para a depuração do programa.
*/

void DEBUG_dictionary(byte_path *dictionary);

#endif // BYTES_DICTIONARY_H