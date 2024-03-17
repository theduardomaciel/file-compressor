#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "utils.h"
#include "stack.h"
#include "priority_queue.h"

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

huffman_node *ht_create_node(void *data, uint64_t frequency, huffman_node *left, huffman_node *right);

int ht_get_tree_size(huffman_node *root);

void ht_pre_order(huffman_node *root, void (*callback)(void *data, void *arg), void *arg);

priority_queue *build_frequency_queue(uint64_t *frequency_table);

int is_leaf(huffman_node *node);

int is_scaped_char(huffman_node *node);

void build_bytes_dictionary(huffman_node *root, stack **bytes_dictionary, stack *path);

huffman_node *build_huffman_tree(priority_queue *queue);

/*
    ⮕ Declarações das funções de impressão
    São funções que imprimem a fila de prioridade e a lista árvore de Huffman de forma visual e em pré-ordem
*/

void pq_print(priority_queue *pq);

void print_tree_visually(huffman_node *node, int level, char direction);

void print_pre_order(huffman_node *root);

void print_dictionary(stack *bytes_dictionary[MAX_SIZE]);

#endif // HUFFMAN_TREE_H