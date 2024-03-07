#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

typedef struct huffman_tree_node
{
    char character;
    int frequency;
    struct huffman_tree_node *
        left,
        *right;
} huffman_tree_node;

typedef struct huffman_tree
{
    huffman_tree_node *root;
} huffman_tree;

huffman_tree *create_huffman_tree();

void insert_huffman_tree(huffman_tree *tree, char character, int frequency);

void print_huffman_tree(huffman_tree *tree);

void destroy_huffman_tree(huffman_tree *tree);

#endif // HUFFMAN_TREE_H