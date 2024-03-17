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
 * Constrói uma fila de prioridade a partir de uma tabela de frequência.
 *
 * Esta função recebe como parâmetro um ponteiro para uma tabela de frequência representada por um array de uint64_t.
 * A tabela de frequência contém a contagem de ocorrências de cada símbolo em um arquivo.
 * A função cria e retorna uma fila de prioridade, onde os elementos são organizados de acordo com suas frequências.
 *
 * @param frequency_table Um ponteiro para a tabela de frequência
 *
 * @return priority_queue* Um ponteiro para a fila de prioridade construída
 */
priority_queue *build_priority_queue(uint64_t *frequency_table);

#endif // FREQUENCY_TABLE_H