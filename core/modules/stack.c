#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "utils.h"
#include "stack.h"

/*
    ⮕ Funções públicas
    São funções que podem ser acessadas por qualquer arquivo que inclua este arquivo
*/

// Função para inicializar a pilha
stack *stack_init()
{
    stack *new_list = malloc(sizeof(stack));
    NULL_POINTER_CHECK(new_list);

    new_list->top = NULL;
    new_list->size = 0;

    return (new_list);
}

// Função para adicionar um elemento no início da pilha
void stack_push(stack *list, void *data)
{
    stack_node *new_node = malloc(sizeof(stack_node));
    NULL_POINTER_CHECK(new_node);

    new_node->data = data;
    new_node->next = list->top;

    list->top = new_node;
    list->size++;
}

// Função para remover um elemento do início da pilha
void *stack_pop(stack *list)
{
    if (list->top == NULL)
    {
        return NULL;
    }

    stack_node *node = list->top;
    void *data = node->data;

    list->top = node->next;
    list->size--;

    free(node);

    return data;
}

// Função para copiar a pilha
stack *stack_copy(stack *list)
{
    stack *new_list = stack_init();
    stack_node *current = list->top;

    while (current != NULL)
    {
        stack_push(new_list, current->data);
        current = current->next;
    }

    return new_list;
}

// Função para destruir a pilha
void stack_destroy(stack *list)
{
    stack_node *current = list->top;
    stack_node *next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    free(list);
}