#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

heap *create_heap(unsigned capacity)
{
    heap *new_heap = (heap *)malloc(sizeof(heap));

    new_heap->size = 0;
    new_heap->capacity = capacity;
    new_heap->nodes = (heap_node **)malloc(new_heap->capacity * sizeof(heap_node *));

    return new_heap;
}

heap_node *new_heap_node(unsigned value, unsigned frequency)
{
    heap_node *new_node = (heap_node *)malloc(sizeof(heap_node));

    new_node->left = new_node->right = NULL;
    new_node->value = value;
    new_node->frequency = frequency;

    return new_node;
}

void swap_nodes(heap_node **a, heap_node **b)
{
    heap_node *temp = *a;
    *a = *b;
    *b = temp;
}

void min_heapify(heap *h, int index)
{
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < h->size && h->nodes[left]->frequency < h->nodes[smallest]->frequency)
    {
        smallest = left;
    }

    if (right < h->size && h->nodes[right]->frequency < h->nodes[smallest]->frequency)
    {
        smallest = right;
    }

    if (smallest != index)
    {
        swap_nodes(&h->nodes[smallest], &h->nodes[index]);
        min_heapify(h, smallest);
    }
}

heap_node *extract_min(heap *h)
{
    if (h->size == 0)
    {
        return NULL;
    }

    heap_node *min = h->nodes[0];
    h->nodes[0] = h->nodes[h->size - 1];
    --h->size;

    min_heapify(h, 0);

    return min;
}

void insert_min_heap(heap *h, heap_node *node)
{
    h->size++;
    int i = h->size - 1;

    while (i > 0 && node->frequency < h->nodes[(i - 1) / 2]->frequency)
    {
        h->nodes[i] = h->nodes[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    h->nodes[i] = node;
}

int is_leaf(heap_node *root)
{
    return !(root->left) && !(root->right);
}

int is_size_one(heap *h)
{
    return h->size == 1;
}

void build_min_heap(heap *h)
{
    int n = h->size - 1;

    for (int i = (n - 1) / 2; i >= 0; --i)
    {
        min_heapify(h, i);
    }
}

void insert_heap(heap *h, heap_node *node)
{
    if (h->size == h->capacity)
    {
        printf("Heap cheia\n");
        return;
    }

    h->size++;
    int i = h->size - 1;

    while (i > 0 && node->frequency < h->nodes[(i - 1) / 2]->frequency)
    {
        h->nodes[i] = h->nodes[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    h->nodes[i] = node;
}

heap *create_and_build_min_heap(char data[], int frequency[], int size)
{
    heap *h = create_heap(size);

    for (int i = 0; i < size; ++i)
    {
        h->nodes[i] = new_heap_node(data[i], frequency[i]);
    }

    h->size = size;
    build_min_heap(h);

    return h;
}