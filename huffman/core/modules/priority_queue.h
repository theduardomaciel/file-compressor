#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "utils.h"

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

// Baseado no código de: https://github.com/nomemory/c-generic-pqueue ❤️

// Estrutura para a fila de prioridade
typedef struct
{
    size_t size;     // Número de elementos na fila de prioridade
    size_t capacity; // Capacidade máxima da fila de prioridade (no caso do algoritmo de Huffman, 256)
    void **data;     // Um array de ponteiros para os dados (heap)
    int (*comparator)(const void *d1, const void *d2);
} priority_queue;

/**
 * Aloca memória para uma nova estrutura de Fila de Prioridade.
 *
 * A função 'compare' funciona da seguinte forma:
 *  retorna 0 se d1 e d2 têm as mesmas prioridades
 *  retorna [valor negativo] se d1 tem uma prioridade menor que d2
 *  retorna [valor positivo] se d1 tem uma prioridade maior que d2
 *
 * @param capacity capacidade inicial da fila de prioridade
 * @param comparator: função de comparação para determinar a prioridade dos elementos
 *
 * @return Um ponteiro para a estrutura de Fila de Prioridade alocada, ou NULL se ocorrer um erro na alocação de memória.
 */
priority_queue *pq_init(int capacity, int (*comparator)(const void *d1, const void *d2));

/**
 * @brief Insere um elemento na fila de prioridade.
 *
 * Esta função insere um elemento na fila de prioridade especificada.
 * O elemento é inserido de acordo com sua prioridade, sendo que elementos com
 * maior prioridade são colocados na frente da fila.
 *
 * @param pq A fila de prioridade onde o elemento será inserido.
 * @param data O ponteiro para os dados do elemento a ser inserido.
 */
void pq_enqueue(priority_queue *pq, const void *data);

/**
 * Remove e retorna o elemento de maior prioridade da fila de prioridade.
 *
 * @param pq A fila de prioridade da qual o elemento será removido.
 * @return O elemento de maior prioridade removido da fila.
 */
void *pq_dequeue(priority_queue *pq);

/**
 * @brief Função responsável por destruir uma fila de prioridade.
 *
 * Esta função libera a memória alocada para a fila de prioridade especificada.
 * Cuidado: os dados armazenados na fila de prioridade não são liberados.
 *
 * @param pq A fila de prioridade a ser destruída.
 */
void pq_destroy(priority_queue *pq);

#endif // PRIORITY_QUEUE_H