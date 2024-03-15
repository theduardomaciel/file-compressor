#include <stdio.h>
#include <stdint.h>

#ifndef FREQUENCY_TABLE_H
#define FREQUENCY_TABLE_H

/**
 * Constrói uma tabela de frequência a partir de um arquivo de entrada.
 *
 * Esta função lê o arquivo de entrada e conta a frequência de ocorrência de cada byte.
 * O resultado é uma tabela de frequência representada por um array de uint64_t, onde cada
 * posição do array corresponde a um byte e o valor da posição indica a quantidade de
 * vezes que o byte aparece no arquivo.
 *
 * @param input O arquivo de entrada a ser lido.
 * @return Um ponteiro para a tabela de frequência construída.
 */
uint64_t *build_frequency_table(FILE *input);

#endif // FREQUENCY_TABLE_H