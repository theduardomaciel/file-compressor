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

/**
 * @brief Inicializa uma árvore de Huffman vazia.
 *
 * @return huffman_node* Um ponteiro para a raiz da árvore de Huffman.
 */
huffman_node *ht_init();

/**
 * @brief Cria um novo nó da árvore de Huffman com os dados, frequência, filho esquerdo e filho direito fornecidos.
 *
 * @param data Os dados a serem armazenados no nó.
 * @param frequency A frequência dos dados.
 * @param left O ponteiro para o filho esquerdo do nó.
 * @param right O ponteiro para o filho direito do nó.
 * @return huffman_node* Um ponteiro para o novo nó criado.
 */
huffman_node *ht_create_node(void *data, uint64_t frequency, huffman_node *left, huffman_node *right);

/**
 * @brief Verifica se um nó da árvore de Huffman é uma folha.
 *
 * @param node O nó a ser verificado.
 * @return 1 se o nó é uma folha, 0 caso contrário.
 */
int is_leaf(huffman_node *node);

/**
 * @brief Verifica se um nó da árvore de Huffman precisa de um caractere de escape.
 *
 * @param node O nó a ser verificado.
 * @return 1 se o nó precisa de um caractere de escape, 0 caso contrário.
 */
int is_scaped_char(huffman_node *node);

/**
 * @brief Obtém o tamanho da árvore de Huffman.
 *
 * @param root A raiz da árvore de Huffman.
 * @return O tamanho da árvore de Huffman.
 */
int ht_get_tree_size(huffman_node *root);

/**
 * @brief Percorre a árvore de Huffman em pré-ordem, chamando a função de retorno fornecida para cada nó visitado.
 *
 * @param root A raiz da árvore de Huffman.
 * @param output_file O arquivo de saída em que a árvore em pré-ordem será escrita.
 */
void ht_pre_order(huffman_node *root, FILE *output_file);

/**
 * @brief Libera a memória alocada para a árvore de Huffman.
 *
 * @param root A raiz da árvore de Huffman.
 */
void ht_destroy(huffman_node *root);

/**
 * @brief Constrói uma árvore de Huffman com base na fila de prioridade fornecida.
 *
 * @param queue A fila de prioridade.
 * @return huffman_node* Um ponteiro para a raiz da árvore de Huffman construída.
 */
huffman_node *build_huffman_tree(priority_queue *queue);

/**
 * @brief Reconstrói uma árvore de Huffman com base na representação em pré-ordem fornecida.
 *
 * @param header_tree A representação em pré-ordem da árvore de Huffman.
 * @return huffman_node* Um ponteiro para a raiz da árvore de Huffman reconstruída.
 */
huffman_node *rebuild_huffman_tree(uint8_t **header_tree);

/*
    ⮕ Declarações das funções de impressão
    São funções que imprimem elementos úteis para a depuração do programa.
*/

void pq_print(priority_queue *pq);

void print_tree_visually(huffman_node *node, int level, char direction);

void print_pre_order(huffman_node *root);

void print_dictionary(stack *bytes_dictionary[MAX_SIZE]);

#endif // HUFFMAN_TREE_H