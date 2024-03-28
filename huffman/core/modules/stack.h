#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "utils.h"

#ifndef STACK_H
#define STACK_H

// Para que a pilha tenha um tamanho dinâmico, utilizamos uma lista encadeada
typedef struct stack_node
{
    void *data;
    struct stack_node *next;
} stack_node;

typedef struct stack
{
    stack_node *top;
} stack;

/**
 * @brief Inicializa uma nova pilha.
 *
 * @return Um ponteiro para a pilha inicializada.
 */
stack *stack_init();

/**
 * @brief Verifica se a pilha está vazia.
 *
 * @param s A pilha a ser verificada.
 * @return 1 se a pilha estiver vazia, 0 caso contrário.
 */
int is_stack_empty(stack *s);

/**
 * @brief Empurra um elemento para o topo da pilha.
 *
 * @param s A pilha onde o elemento será empurrado.
 * @param data O ponteiro para os dados a serem empurrados para a pilha.
 */
void stack_push(stack *s, void *data);

/**
 * @brief Remove e retorna o elemento do topo da pilha.
 *
 * @param s A pilha da qual o elemento será removido.
 * @return O ponteiro para os dados removidos do topo da pilha.
 */
void *stack_pop(stack *s);

/**
 * @brief Cria uma cópia da pilha fornecida.
 *
 * @param s A pilha a ser copiada.
 * @return A cópia da pilha.
 */
stack *stack_copy(stack *s);

/**
 * @brief Destrói uma pilha, liberando a memória alocada.
 * Cuidado ao usar esta função, pois ela não libera a memória dos dados armazenados na pilha.
 *
 * @param s A pilha a ser destruída.
 */
void stack_destroy(stack *s);

#endif // STACK_H