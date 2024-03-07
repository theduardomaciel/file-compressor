#include <stdio.h>
#include <stdlib.h>

#include "huffman_tree.h"
#include "heap.h"

// Função que cria um novo nó
huffman_tree_node *new_node(unsigned char item, int freq)
{
    huffman_tree_node *new = (huffman_tree_node *)malloc(sizeof(huffman_tree_node));
    new->character = item;
    new->frequency = freq;
    new->left = NULL;
    new->right = NULL;
    return new;
}

// Função que cria uma nova fila de prioridade com a Heap
heap *create_priority_queue(int capacity)
{
    return create_heap(capacity);
}