#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "huffman_tree.h"
#include "priority_queue.h"

#include "utils.h"

#ifndef FREQUENCY_TABLE_H
#define FREQUENCY_TABLE_H

/**
 * @brief Constrói uma tabela de frequência a partir de um arquivo de entrada.
 *
 * Esta função lê o arquivo de entrada e conta a frequência de ocorrência de cada byte.
 * O resultado é uma tabela de frequência representada por um array de uint64_t, onde cada
 * posição do array corresponde a um byte e o valor da posição indica a quantidade de
 * vezes que o byte aparece no arquivo.
 *
 * @param input O arquivo de entrada a ser lido.
 * @return uint64_t* Um ponteiro para a tabela de frequência construída.
 */
uint64_t *build_frequency_table(FILE *input);

/**
 * @brief Constrói uma fila de prioridade com base na tabela de frequências fornecida.
 *
 * @param frequency_table A tabela de frequências.
 * @return priority_queue* Um ponteiro para a fila de prioridade construída.
 */
priority_queue *build_frequency_queue(uint64_t *frequency_table);

/**
 * @brief Constrói um dicionário de bytes com base na árvore de Huffman fornecida.
 *
 * @param root A raiz da árvore de Huffman.
 * @param bytes_dictionary Um ponteiro para o dicionário de bytes a ser construído.
 * @param path O caminho atual na árvore de Huffman.
 */
void build_bytes_dictionary(huffman_node *root, stack **bytes_dictionary, stack *path);

// Obs.: No futuro, buscar transformar a função acima em uma função que retorna um ponteiro para um dicionário de bytes
// Atualmente não é possível pois nenhuma sugestão de solução que não utilize recursão foi encontrada

#endif // FREQUENCY_TABLE_H