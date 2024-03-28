#include "stack.h"

/*
    ⮕ Funções públicas
    São funções que podem ser acessadas por qualquer arquivo que inclua este arquivo
*/

stack *stack_init()
{
    stack *new_stack = malloc(sizeof(stack));
    NULL_POINTER_CHECK(new_stack);

    new_stack->top = NULL;

    return new_stack;
}

int is_stack_empty(stack *stack)
{
    return stack->top == NULL;
}

void stack_push(stack *stack, void *data)
{
    stack_node *new_node = malloc(sizeof(stack_node));
    NULL_POINTER_CHECK(new_node);

    new_node->data = data;
    new_node->next = stack->top;

    stack->top = new_node;
}

void *stack_pop(stack *stack)
{
    if (stack->top == NULL)
    {
        return NULL;
    }

    stack_node *temp_node = stack->top;
    void *popped_data = temp_node->data;

    stack->top = temp_node->next;

    free(temp_node);
    return popped_data;
}

stack *stack_copy(stack *s)
{
    stack *new_stack = stack_init();
    stack_node *current = s->top;

    while (current != NULL)
    {
        stack_push(new_stack, current->data);
        current = current->next;
    }

    return new_stack;
}

void stack_destroy(stack *s)
{
    while (!is_stack_empty(s))
    {
        stack_pop(s);
    }
}