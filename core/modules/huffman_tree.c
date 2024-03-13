#include <stdio.h>
#include <stdlib.h>

#include "huffman_tree.h"
#include "heap.h"

heap *build_huffman_tree(char *data, unsigned *frequencies, unsigned size)
{
    heap_node *left, *right, *top;

    heap *h = create_and_build_min_heap(data, frequencies, size);

    while (h->size != 1)
    {
        left = extract_min(h);
        right = extract_min(h);

        top = new_heap_node('*', left->frequency + right->frequency);
        top->left = left;
        top->right = right;

        insert(h, top);
    }

    return extract_min(h);
}

void destroy_huffman_tree(heap *tree)
{
    destroy_heap(tree);
}

void print_codes(heap_node *root, int values[], int top)
{
    if (root->left)
    {
        values[top] = 0;
        print_codes(root->left, values, top + 1);
    }

    if (root->right)
    {
        values[top] = 1;
        print_codes(root->right, values, top + 1);
    }

    if (root->left == NULL && root->right == NULL)
    {
        printf("%c: ", root->value);
        for (int i = 0; i < top; i++)
        {
            printf("%d", values[i]);
        }
        printf("\n");
    }
}