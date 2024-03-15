#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "utils.h"

#include "huffman_tree.h"
#include "priority_queue.h"

huffman_node *ht_init()
{
    huffman_node *tree = malloc(sizeof(huffman_node));
    return tree;
}

huffman_node *ht_create_node(void *data, uint64_t frequency, huffman_node *left, huffman_node *right)
{
    huffman_node *node = malloc(sizeof(huffman_node));

    node->data = data;
    node->frequency = frequency;
    node->left = left;
    node->right = right;

    return node;
}

int compare(const void *d1, const void *d2)
{
    huffman_node *n1 = (huffman_node *)d1;
    huffman_node *n2 = (huffman_node *)d2;

    if (n1->frequency == n2->frequency)
    {
        return 0;
    }
    else if (n1->frequency > n2->frequency) // cuidado com esse sinal! não inverta!
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

void pq_print(priority_queue *pq)
{
    NULL_POINTER_CHECK(pq);

    if (pq == NULL)
    {
        DEBUG("A fila de prioridade não foi inicializada.\n");
        return;
    }

    for (size_t i = 0; i < pq->size; i++)
    {
        huffman_node *node = (huffman_node *)pq->data[i];
        uint8_t data = *(uint8_t *)node->data;

        printf("%d (%ld)\n", data, node->frequency);
        // para exibir texto: printf("%c (%ld)\n", (char *)data, node->frequency);
    }
    printf("\n");
}

priority_queue *build_priority_queue(uint64_t *frequency_table)
{
    priority_queue *queue = init_priority_queue(MAX_SIZE, compare);

    // Adiciona todos os bytes que aparecem no arquivo (têm frequência maior que 0) na fila de prioridade
    for (uint64_t i = 0; i < MAX_SIZE; i++)
    {
        uint64_t current_frequency = frequency_table[i];

        if (current_frequency > 0)
        {
            uint8_t *data = malloc(sizeof(uint8_t));
            *data = i;

            printf("Enfileirando %c com prioridade %lu\n", *data, current_frequency);
            pq_enqueue(queue, ht_create_node(data, current_frequency, NULL, NULL));
        }
    }

    return queue;
}

huffman_node *build_huffman_tree(priority_queue *queue)
{
    if (queue->size == 1)
    {
        huffman_node *node = (huffman_node *)pq_dequeue(queue);
        huffman_node *root = malloc(sizeof(huffman_node));

        root->data = malloc(sizeof(uint8_t));
        *(uint8_t *)root->data = '*';

        root->frequency = node->frequency;
        root->left = NULL;
        root->right = node;

        return root;
    }
    else
    {
        while (queue->size > 1)
        {
            // printf("Tamanho da fila: %lu\n", queue->size);

            huffman_node *left = (huffman_node *)pq_dequeue(queue);
            huffman_node *right = (huffman_node *)pq_dequeue(queue);

            // Seguindo as especificações do projeto, o nó pai terá um caractere nulo (asterisco)
            void *parent_data = malloc(sizeof(uint8_t));
            *(uint8_t *)parent_data = '*';

            uint64_t summed_frequencies = left->frequency + right->frequency;
            // printf("Frequências somadas (%ld + %ld): %ld\n", left->frequency, right->frequency, summed_frequencies);

            printf("🖇️  Selecionando os dois nós com menor frequência para unir:\n");
            /* printf("Esquerda: %c, freq.: %d | ", left->character, left->frequency);
            printf("Direita: %c, freq.: %d\n", right->character, right->frequency);
            printf("Logo, o novo pai %c possui frequência %d\n", parent->character, parent->frequency); */
            printf("          \t\tEsquerda\tDireita\t\tPai\n");
            printf("Caractere\t\t%d\t\t%d\t\t%c\n", *(uint8_t *)left->data, *(uint8_t *)right->data, '*');
            printf("Frequência\t\t%d\t\t%d\t\t%d\n", left->frequency, right->frequency, summed_frequencies);
            printf("--------------------\n");

            pq_enqueue(queue, ht_create_node(parent_data, summed_frequencies, left, right));
        }

        return (huffman_node *)pq_dequeue(queue);
    }
}

void print_pre_order(huffman_node *root)
{
    if (root != NULL)
    {
        printf("%c (%ld)\n", *(uint8_t *)(char *)root->data, root->frequency);
        print_pre_order(root->left);
        print_pre_order(root->right);
    }
}

void print_tree_visually(huffman_node *node, int level, char direction)
{
    if (node != NULL)
    {
        print_tree_visually(node->right, level + 1, '/');

        for (int i = 0; i < level; i++)
        {
            printf("   ");
        }

        printf("%c%c (%ld)\n", direction, *(uint8_t *)(char *)node->data, node->frequency);

        print_tree_visually(node->left, level + 1, '\\');
    }
}