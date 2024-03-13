#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

/**
 * Estrutura de uma pilha.
 */
struct stack
{
    int top;
    unsigned capacity;
    int *array;
};

/**
 * Cria uma pilha com a capacidade fornecida.
 *
 * @param capacity A capacidade da pilha.
 * @return Um ponteiro para a pilha criada.
 */
struct stack *create_stack(unsigned capacity);

/**
 * Verifica se a pilha está vazia.
 *
 * @param stack A pilha a ser verificada.
 * @return true se a pilha estiver vazia, false caso contrário.
 */

bool is_empty(struct stack *stack);

/**
 * Verifica se a pilha está cheia.
 *
 * @param stack A pilha a ser verificada.
 * @return true se a pilha estiver cheia, false caso contrário.
 */
bool is_full(struct stack *stack);

/**
 * Adiciona um item à pilha.
 *
 * @param stack A pilha a ser modificada.
 * @param item O item a ser adicionado à pilha.
 */
void push(struct stack *stack, int item);

/**
 * Remove um item da pilha.
 *
 * @param stack A pilha a ser modificada.
 * @return O item removido da pilha.
 */

int pop(struct stack *stack);

#endif // STACK_H