#include <stdint.h>
#include "priority_queue.h"

#define MAX_SIZE 256
// Para mais informações do porquê podemos usar o número 256, veja o arquivo docs/bytes.md

#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

typedef struct huffman_node
{
    void *data;
    uint64_t frequency;
    struct huffman_node *left;
    struct huffman_node *right;
} huffman_node;

huffman_node *ht_init();

priority_queue *build_priority_queue(uint64_t *frequency_table);

huffman_node *ht_create_node(void *data, uint64_t frequency, huffman_node *left, huffman_node *right);

huffman_node *build_huffman_tree(priority_queue *queue);

/*
    ⮕ Declarações das funções de impressão
    São funções que imprimem a fila de prioridade e a lista árvore de Huffman de forma visual e em pré-ordem
*/

void pq_print(priority_queue *pq);

void print_tree_visually(huffman_node *node, int level, char direction);

void print_pre_order(huffman_node *root);

#endif // HUFFMAN_TREE_H