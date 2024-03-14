#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "huffman_tree.h"
#include "frequency_table.h"

huffman_tree_node *create_huffman_tree_node(char character, int frequency)
{
    huffman_tree_node *node = (huffman_tree_node *)malloc(sizeof(huffman_tree_node));
    node->character = character;
    node->frequency = frequency;
    node->left = NULL;
    node->right = NULL;
    node->next = NULL;
    return node;
}

void add_huffman_tree_node(huffman_tree *tree, char character, int frequency)
{
    huffman_tree_node *node = create_huffman_tree_node((unsigned char)character, frequency);
    insert_huffman_tree_node(tree, node);
}

void insert_huffman_tree_node(huffman_tree *tree, huffman_tree_node *node)
{
    if (tree->root == NULL)
    {
        tree->root = node;
    }
    else
    {
        huffman_tree_node *current = tree->root;
        huffman_tree_node *previous = NULL;

        while (current != NULL && current->frequency < node->frequency)
        {
            previous = current;
            current = current->next;
        }

        if (previous == NULL)
        {
            node->next = tree->root;
            tree->root = node;
        }
        else
        {
            previous->next = node;
            node->next = current;
        }
    }
}

huffman_tree_node *pop_huffman_tree_node(huffman_tree *tree)
{
    if (tree->root == NULL)
    {
        return NULL;
    }

    huffman_tree_node *node = tree->root;
    tree->root = tree->root->next;

    return node;
}

huffman_tree_node *merge_huffman_tree_nodes(huffman_tree_node *left, huffman_tree_node *right)
{
    huffman_tree_node *parent = create_huffman_tree_node('*', left->frequency + right->frequency);

    parent->left = left;
    parent->right = right;
    parent->next = NULL;

    return parent;
}

char *char_conversion_helper(huffman_tree_node *node, char *data)
{
    if (node != NULL)
    {
        if (node->character == '*' || node->character == '\\')
        {
            strcat(data, "\\");
        }

        data = strcat(data, &node->character);
        char_conversion_helper(node->left, data);
        char_conversion_helper(node->right, data);
    }
}

char *convert_huffman_tree_to_string(huffman_tree *tree)
{
    char *data = "";
    data = char_conversion_helper(tree->root, data);
    return data;
}

int is_leaf(huffman_tree_node *node)
{
    return node->left == NULL && node->right == NULL;
}

void tree_paths_helper(huffman_tree_node *node, char *path, char **paths)
{
    if (is_leaf(node))
    {
        /* paths[node->character] = malloc(sizeof(path));
        strcpy(paths[node->character], path); */
        paths[node->character] = path;
        printf("Caractere: %c, Path: %s\n", node->character, path);
    }
    else
    {
        if (node->left != NULL)
        {
            char left_path[256];
            strcpy(left_path, path);
            strcat(left_path, "0");
            tree_paths_helper(node->left, left_path, paths);
        }

        if (node->right != NULL)
        {
            char right_path[256];
            strcpy(right_path, path);
            strcat(right_path, "1");
            tree_paths_helper(node->right, right_path, paths);
        }
    }
}

char **get_huffman_tree_paths(huffman_tree *tree)
{
    char **paths = (char **)malloc(256 * sizeof(char *));

    for (int i = 0; i < 256; i++)
    {
        paths[i] = malloc(sizeof(unsigned char) * 8);
    }

    char path[256] = "";

    tree_paths_helper(tree->root, path, paths);

    return paths;
}

huffman_tree *initialize_huffman_tree()
{
    huffman_tree *tree = (huffman_tree *)malloc(sizeof(huffman_tree));
    tree->root = NULL;
    tree->stringfied = "";
    tree->paths = (char **)malloc(256 * sizeof(char *));
    tree->char_frequency = (int *)malloc(256 * sizeof(int));
    return tree;
}

void print_tree_visually(huffman_tree_node *node, int level, char direction)
{
    if (node != NULL)
    {
        print_tree_visually(node->right, level + 1, '/');

        for (int i = 0; i < level; i++)
        {
            printf("   ");
        }

        printf("%c%c (%d)\n", direction, node->character, node->frequency);

        print_tree_visually(node->left, level + 1, '\\');
    }
}

huffman_tree *create_huffman_tree(int *frequency_table)
{
    huffman_tree *tree = initialize_huffman_tree();

    printf("1️⃣. Criando nós para cada caractere do arquivo com base na seguinte tabela de frequência:\n\n");

    // Criamos um nó para cada sequencia de bytes que aparece no arquivo
    for (int i = 0; i < 256; i++)
    {
        if (frequency_table[i] > 0)
        {
            add_huffman_tree_node(tree, i, frequency_table[i]);
            printf("Caractere: %c | Frequência: %d\n", i, frequency_table[i]);
        }
    }

    printf("\n");
    printf("2️⃣. Realizando a montagem da árvore de Huffman...\n\n");

    while (tree->root->next != NULL)
    {
        huffman_tree_node *left = pop_huffman_tree_node(tree);
        huffman_tree_node *right = pop_huffman_tree_node(tree);

        huffman_tree_node *parent = merge_huffman_tree_nodes(left, right);

        printf("🖇️  Selecionando os dois nós com menor frequência para unir:\n");
        /* printf("Esquerda: %c, freq.: %d | ", left->character, left->frequency);
        printf("Direita: %c, freq.: %d\n", right->character, right->frequency);
        printf("Logo, o novo pai %c possui frequência %d\n", parent->character, parent->frequency); */
        printf("          \t\tEsquerda\tDireita\t\tPai\n");
        printf("Caractere\t\t%c\t\t%c\t\t%c\n", left->character, right->character, parent->character);
        printf("Frequência\t\t%d\t\t%d\t\t%d\n", left->frequency, right->frequency, parent->frequency);
        printf("--------------------\n");

        insert_huffman_tree_node(tree, parent);
    }

    tree->char_frequency = frequency_table;
    tree->paths = get_huffman_tree_paths(tree);
    /* tree->stringfied = convert_huffman_tree_to_string(tree);

    // Imprimimos a árvore de Huffman
    printf("\n");
    printf("🌲 Árvore de Huffman:\n");
    for (int i = 0; i < 256; i++)
    {
        if (tree->paths[i] != NULL)
        {
            printf("Caractere: %c, Frequência: %d, Path: %s\n", i, tree->char_frequency[i], tree->paths[i]);
        }
    } */

    print_tree_visually(tree->root, 0, '-');

    return tree;
}
