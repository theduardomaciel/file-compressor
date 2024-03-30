#include "utils.h"
#include "huffman_tree.h"

#ifndef FREQUENCY_H
#define FREQUENCY_H

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

#endif // FREQUENCY_H