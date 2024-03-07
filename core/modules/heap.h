#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int size;
    int capacity;
    int *data;
} heap;

heap *create_heap(int capacity);

void insert(heap *h, int value);

int remove_min(heap *h);

void destroy_heap(heap *h);

#endif // HEAP_H