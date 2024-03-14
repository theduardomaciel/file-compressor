#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

typedef struct huffman_tree_node huffman_tree_node;

struct huffman_tree_node
{
    char character;
    int frequency;
    huffman_tree_node *left;
    huffman_tree_node *right;
    huffman_tree_node *next; // unimos as estruturas em uma lista encadeada
};

typedef struct
{
    huffman_tree_node *root;
    char *stringfied;
    char **paths;
    int *char_frequency;
} huffman_tree;

huffman_tree *create_huffman_tree(int *frequency);

void add_huffman_tree_node(huffman_tree *tree, char character, int frequency);

char **get_huffman_tree_paths(huffman_tree *tree);

void insert_huffman_tree_node(huffman_tree *tree, huffman_tree_node *node);

huffman_tree_node *merge_huffman_tree_nodes(huffman_tree_node *left, huffman_tree_node *right);

char *convert_huffman_tree_to_string(huffman_tree *tree);

huffman_tree_node *pop_huffman_tree_node(huffman_tree *tree);

int is_leaf(huffman_tree_node *node);

#endif // HUFFMAN_TREE_H