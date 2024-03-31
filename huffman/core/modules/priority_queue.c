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

void pq_heapify(priority_queue *pq, size_t index);
void swap(void **a, void **b);

/*
    ⮕ Funções públicas
    São funções que podem ser acessadas por qualquer arquivo que inclua este arquivo
*/

priority_queue *pq_init(int capacity, int (*comparator)(const void *, const void *))
{
    priority_queue *new_pq = malloc(sizeof(priority_queue));
    NULL_POINTER_CHECK(new_pq);
    NULL_POINTER_CHECK(comparator);

    // Inicializamos os campos da fila de prioridade
    new_pq->size = 0;
    new_pq->capacity = capacity;
    new_pq->comparator = comparator;

    // Alocamos memória para o array de dados da heap com base na capacidade máxima
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

    // Esse índice será usado para reorganizar a fila de prioridade
    size_t index;

    // Adicionamos o elemento no final da fila de prioridade
    pq->data[pq->size] = (void *)data;
    index = pq->size;
    pq->size++;

    // Reorganizamos a fila de prioridade a fim de restaurar a propriedade de heap
    // Ou seja, o novo elemento troca de posição com seu pai enquanto sua precedência for maior
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

/**
 * Função responsável por reorganizar o heap da fila de prioridade a partir de um determinado índice.
 *
 * @param pq A fila de prioridade.
 * @param index O índice a partir do qual o heap será reorganizado.
 */
void pq_heapify(priority_queue *pq, size_t index)
{
    if (pq == NULL)
    {
        DEBUG("A fila de prioridade não foi inicializada.\n");
        return;
    }

    size_t largest_index;

    // Calculamos os índices dos filhos esquerdo e direito
    size_t left_index = LEFT(index);
    size_t right_index = RIGHT(index);

    // Verificamos se o filho esquerdo é maior que o pai
    if (left_index < pq->size && pq->comparator(pq->data[left_index], pq->data[index]) > 0)
    {
        largest_index = left_index;
    }
    else
    {
        largest_index = index;
    }

    // Verificamos se o filho direito é maior que o maior entre o pai e o filho esquerdo
    if (right_index < pq->size && pq->comparator(pq->data[right_index], pq->data[largest_index]) > 0)
    {
        largest_index = right_index;
    }

    // A esse ponto, o maior elemento entre o pai e os filhos foi encontrado
    // Portanto, se o maior elemento não for o pai, trocamos o pai com o maior elemento
    if (largest_index != index)
    {
        swap(&pq->data[index], &pq->data[largest_index]);

        // Chamamos a função recursivamente para o filho que foi trocado
        pq_heapify(pq, largest_index);
    }
}

/**
 * Função responsável por trocar os valores de dois ponteiros.
 *
 * @param a O endereço do primeiro ponteiro.
 * @param b O endereço do segundo ponteiro.
 */
void swap(void **a, void **b)
{
    void *temp = *a;
    *a = *b;
    *b = temp;
}