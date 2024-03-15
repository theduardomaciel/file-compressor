#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "priority_queue.h"

/*
    ⮕ Macros úteis
    São usados para calcular o índice do filho esquerdo, direito e pai de um nó
*/
#define LEFT(x) (2 * (x) + 1)
#define RIGHT(x) (2 * (x) + 2)
#define PARENT(x) ((x) / 2)

/*
    ⮕ Declarações das funções estáticas
    São funções que só podem ser acessadas por funções deste arquivo
*/

/**
 * Função responsável por reorganizar o heap da fila de prioridade a partir de um determinado índice.
 *
 * @param pq A fila de prioridade.
 * @param index O índice a partir do qual o heap será reorganizado.
 */
void pq_heapify(priority_queue *pq, size_t index);

/**
 * Função responsável por trocar os valores de dois ponteiros.
 *
 * @param a O endereço do primeiro ponteiro.
 * @param b O endereço do segundo ponteiro.
 */
void swap(void **a, void **b);

/*
    ⮕ Funções públicas
    São funções que podem ser acessadas por qualquer arquivo que inclua este arquivo
*/

// Função para inicializar a fila de prioridade
priority_queue *init_priority_queue(int capacity, int (*comparator)(const void *d1, const void *d2))
{
    priority_queue *new_pq = NULL;
    NULL_POINTER_CHECK(comparator);

    // Alocamos memória para a fila de prioridade
    new_pq = malloc(sizeof(priority_queue));
    NULL_POINTER_CHECK(new_pq);

    // Obs: É possível declarar a variável e alocar memória em uma única linha
    // NULL_POINTER_CHECK(new_pq = malloc(sizeof(priority_queue)));

    // Inicializamos os campos da fila de prioridade
    new_pq->comparator = comparator;
    new_pq->size = 0;
    new_pq->capacity = capacity;

    // A representação interna de "data" dentro da fila de prioridade é um array de ponteiros void
    new_pq->data = malloc(capacity * sizeof(*(new_pq->data)));
    NULL_POINTER_CHECK(new_pq->data);

    return (new_pq);
}

void pq_destroy(priority_queue *pq)
{
    if (pq == NULL)
    {
        DEBUG("A fila de prioridade está vazia. Não há nada para liberar.\n");
        return;
    }

    free(pq->data);
    free(pq);
}

void pq_enqueue(priority_queue *pq, const void *data)
{
    NULL_POINTER_CHECK(pq);

    if (pq == NULL)
    {
        DEBUG("A fila de prioridade não foi inicializada.\n");
        return;
    }

    if (pq->size >= pq->capacity)
    {
        DEBUG("A fila de prioridade está cheia. Não é possível adicionar mais elementos.\n");
        return;
    }

    size_t index;
    // void *temp = NULL;

    // Adicionamos o elemento no final da fila de prioridade
    pq->data[pq->size] = (void *)data;
    index = pq->size;
    pq->size++;

    // O novo elemento é trocado com seu pai enquanto sua precedência for maior
    while (index > 0 && pq->comparator(pq->data[index], pq->data[PARENT(index)]) > 0)
    {
        swap(&pq->data[index], &pq->data[PARENT(index)]);
        index = PARENT(index);
    }
}

void *pq_dequeue(priority_queue *pq)
{
    NULL_POINTER_CHECK(pq);

    if (pq == NULL)
    {
        DEBUG("A fila de prioridade não foi inicializada.\n");
        return NULL;
    }

    if (pq->size == 0)
    {
        DEBUG("A fila de prioridade está vazia. Não é possível remover elementos.\n");
        return NULL;
    }

    void *data = pq->data[0];
    pq->data[0] = pq->data[pq->size - 1];
    pq->size--;

    // Reorganizamos a fila de prioridade a fim de restaurar a propriedade de heap
    pq_heapify(pq, 0);

    return (data);
}

// ⮕ Funções estáticas

void pq_heapify(priority_queue *pq, size_t index)
{
    NULL_POINTER_CHECK(pq);

    if (pq == NULL)
    {
        DEBUG("A fila de prioridade não foi inicializada.\n");
        return;
    }

    size_t largest;
    // void *temp = NULL;

    // Calculamos os índices dos filhos esquerdo e direito
    size_t left = LEFT(index);
    size_t right = RIGHT(index);

    // Verificamos se o filho esquerdo é maior que o pai
    if (left < pq->size && pq->comparator(pq->data[left], pq->data[index]) > 0)
    {
        largest = left;
    }
    else
    {
        largest = index;
    }

    // Verificamos se o filho direito é maior que o maior entre o pai e o filho esquerdo
    if (right < pq->size && pq->comparator(pq->data[right], pq->data[largest]) > 0)
    {
        largest = right;
    }

    // A esse ponto, o maior elemento entre o pai e os filhos foi encontrado
    if (largest != index)
    {
        // Portanto, se o maior elemento não for o pai, trocamos o pai com o maior elemento
        swap(&pq->data[index], &pq->data[largest]);

        // Chamamos a função recursivamente para o filho que foi trocado
        pq_heapify(pq, largest);
    }
}

void swap(void **a, void **b)
{
    void *temp = *a;
    *a = *b;
    *b = temp;
}