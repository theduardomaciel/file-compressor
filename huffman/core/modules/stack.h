#include <stdlib.h>
#include <stdint.h>

#ifndef STACK_H
#define STACK_H

typedef struct stack_node
{
    void *data;
    struct stack_node *next;
} stack_node;

typedef struct stack
{
    stack_node *top;
    uint64_t size;
} stack;

stack *stack_init();

void stack_push(stack *s, void *data);

void *stack_pop(stack *s);

stack *stack_copy(stack *s);

void stack_destroy(stack *s);

#endif // STACK_H