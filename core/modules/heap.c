#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

// Função que cria uma nova Heap
heap *create_heap(int capacity)
{
    heap *new = (heap *)malloc(sizeof(heap));
    new->size = 0;
    new->capacity = capacity;
    new->data = (int *)malloc(capacity * sizeof(int));
    return new;
}

// Função que insere um novo valor na Heap
void insert(heap *h, int value)
{
    if (h->size == h->capacity)
    {
        printf("Heap cheia\n");
        return;
    }

    int i = h->size;
    h->data[i] = value;

    while (i > 0 && h->data[i] < h->data[(i - 1) / 2])
    {
        int temp = h->data[i];
        h->data[i] = h->data[(i - 1) / 2];
        h->data[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }

    h->size++;
}

// Função que remove o menor valor da Heap
int remove_min(heap *h)
{
    if (h->size == 0)
    {
        printf("Heap vazia\n");
        return -1;
    }

    int min = h->data[0];
    h->data[0] = h->data[h->size - 1];
    h->size--;

    int i = 0;
    while (2 * i + 1 < h->size)
    {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = left;

        if (right < h->size && h->data[right] < h->data[left])
        {
            smallest = right;
        }

        if (h->data[i] < h->data[smallest])
        {
            break;
        }

        int temp = h->data[i];
        h->data[i] = h->data[smallest];
        h->data[smallest] = temp;
        i = smallest;
    }

    return min;
}