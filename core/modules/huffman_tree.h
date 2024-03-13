#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include "heap.h"

/**
 * Constrói uma árvore de Huffman com base nos dados e frequências fornecidos.
 *
 * @param data Os dados a serem comprimidos.
 * @param frequencies As frequências dos dados.
 * @param size O tamanho dos dados.
 * @return Um ponteiro para a árvore de Huffman construída.
 */
heap *build_huffman_tree(char *data, unsigned *frequencies, unsigned size);

/**
 * Destroi a árvore de Huffman fornecida, liberando a memória alocada.
 *
 * @param tree A árvore de Huffman a ser destruída.
 */
void destroy_huffman_tree(heap *tree);

/**
 * Imprime os códigos de Huffman para cada caractere.
 *
 * Esta função recebe a raiz de uma árvore de Huffman, um array de inteiros
 * representando os valores dos caracteres e o tamanho do array. Ela imprime
 * os códigos de Huffman correspondentes a cada caractere.
 *
 * @param root A raiz da árvore de Huffman.
 * @param values O array de inteiros representando os valores dos caracteres.
 * @param top O tamanho do array de inteiros.
 */
void print_codes(heap_node *root, int values[], int top);

#endif // HUFFMAN_TREE_H