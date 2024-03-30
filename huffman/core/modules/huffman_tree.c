#include "huffman_tree.h"

/*
    ⮕ Funções públicas
    São funções que podem ser acessadas por qualquer arquivo que inclua este arquivo
*/

huffman_node *ht_init()
{
    huffman_node *tree = malloc(sizeof(huffman_node));
    tree->data = NULL;
    tree->frequency = 0;
    tree->left = NULL;
    tree->right = NULL;
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

int is_leaf(huffman_node *node)
{
    return node->left == NULL && node->right == NULL;
}

int is_scaped_char(huffman_node *node)
{
    // Verificamos se o caractere é uma barra invertida ou um asterisco
    // Nesses dois casos precisamos de um caractere de escape
    // Verifique o arquivo docs/nodes.md para mais informações
    return *(uint8_t *)node->data == '\\' || *(uint8_t *)node->data == '*';
}

void ht_write_pre_order(huffman_node *root, FILE *output_file)
{
    if (root == NULL)
    {
        return;
    }

    // Escrevemos um caractere de escape '\' antes do nó atual caso ele seja uma folha que possa ser confundida com um nó interno
    // Isso pode vir a acontecer pois o caractere '*' é utilizado para representar nós internos, e os nós folha podem assumir qualquer valor
    // Portanto, precisamos de um caractere de escape para diferenciar os dois tipos de nós
    if (is_leaf(root) && is_scaped_char(root))
    {
        char escape_char = '\\';
        fwrite(&escape_char, sizeof(uint8_t), 1, output_file);
    }

    // Escrevemos o caractere atual no header do arquivo
    fwrite((uint8_t *)root->data, sizeof(uint8_t), 1, output_file);

    // Percorremos a árvore de Huffman em pré-ordem
    ht_write_pre_order(root->left, output_file);
    ht_write_pre_order(root->right, output_file);
}

int ht_get_tree_size(huffman_node *root)
{
    // Condição de parada: se a árvore estiver vazia, ou seja, seu tamanho é 0
    if (root == NULL)
    {
        return 0;
    }

    // Iniciamos um contador para o nó atual
    int size = 1;

    // Caso o nó atual seja uma folha que pode ser confundida com um nó interno,
    // incrementamos o tamanho em +1 para considerar o caractere de escape
    if (is_leaf(root) && is_scaped_char(root))
    {
        size++;
    }

    // Em seguida, calculamos o tamanho dos subárvores esquerda e direita recursivamente
    size += ht_get_tree_size(root->left);
    size += ht_get_tree_size(root->right);

    return size;
}

void ht_destroy(huffman_node *root)
{
    if (root != NULL)
    {
        ht_destroy(root->left);
        ht_destroy(root->right);
        free(root->data);
        free(root);
    }
}

huffman_node *build_huffman_tree(priority_queue *queue)
{
    NULL_POINTER_CHECK(queue);

    // Garantimos que ainda existem nós na fila
    while (queue->size > 1)
    {
        // Desenfileiramos os dois nós com menores frequências
        huffman_node *left = (huffman_node *)pq_dequeue(queue);
        huffman_node *right = (huffman_node *)pq_dequeue(queue);

        // Seguindo as especificações do projeto, o nó interno/pai terá como caractere um asterisco ('*')
        // Por estarmos utilizando um ponteiro para void, precisamos alocar memória para esse caractere
        void *parent_data = malloc(sizeof(uint8_t));
        *(uint8_t *)parent_data = '*';

        // A frequência do nó interno/pai é a soma das frequências dos dois nós filhos
        uint64_t summed_frequencies = left->frequency + right->frequency;

        // Criamos um novo nó com os dois nós desempilhados como filhos e o enfileiramos
        pq_enqueue(queue, ht_create_node(parent_data, summed_frequencies, left, right));
    }

    return (huffman_node *)pq_dequeue(queue);
}

huffman_node *rebuild_huffman_tree(uint8_t **pre_order_tree)
{
    // Alocamos espaço para armazenar o símbolo atual da árvore
    uint8_t *item = malloc(sizeof(uint8_t));
    uint8_t *current_symbol = *pre_order_tree; // Obtém o símbolo atual da árvore

    // Obs.: Ao utilizar (*pre_order_tree)++ estamos avançando para o próximo símbolo

    // Se o símbolo atual for '*', indica um nó interno
    if (*current_symbol == '*')
    {
        *item = '*';
        (*pre_order_tree)++;

        // Reconstruímos as subárvores esquerda e direita recursivamente
        huffman_node *left = rebuild_huffman_tree(pre_order_tree);
        huffman_node *right = rebuild_huffman_tree(pre_order_tree);

        // Criamos um nó com as subárvores esquerda e direita
        return ht_create_node((void *)item, 0, left, right);
    }
    else
    {
        // Se o símbolo atual for '\', indica que o próximo símbolo é um caractere especial,
        // portanto, avançamos para o próximo símbolo e o armazenamos em item
        if (*current_symbol == '\\')
        {
            (*pre_order_tree)++;
            *item = **pre_order_tree;
            (*pre_order_tree)++;
        }
        else
        {
            // Caso contrário, o símbolo atual é um caractere normal, então o armazenamos em item e avançamos para o próximo símbolo
            *item = *current_symbol;
            (*pre_order_tree)++;
        }

        // Criamos e retornamos um nó da árvore de Huffman com o símbolo atual
        huffman_node *node = ht_create_node((void *)item, 0, NULL, NULL);
        return node;
    }
}

// ⮕ Funções de impressão

void pq_print(priority_queue *pq)
{
    NULL_POINTER_CHECK(pq);

    if (pq == NULL)
    {
        DEBUG("A fila de prioridade não foi inicializada.\n");
        return;
    }

    priority_queue *pq_copy = pq_init(pq->capacity, pq->comparator);

    for (size_t i = 0; i < pq->size; i++)
    {
        pq_enqueue(pq_copy, pq->data[i]);
    }

    printf("\nFila de prioridade:\n");

    while (pq_copy->size > 0)
    {
        huffman_node *node = (huffman_node *)pq_dequeue(pq_copy);
        printf("%c (%lu)", *(uint8_t *)node->data, node->frequency);
        if (pq_copy->size > 0)
        {
            printf(" | ");
        }
    }

    printf("\n\n");
}

void print_pre_order(huffman_node *root)
{
    if (root != NULL)
    {
        printf("%d (%ld)\n", *(uint8_t *)root->data, root->frequency);

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

        printf("%c(%c)\n", direction, *(uint8_t *)node->data);

        print_tree_visually(node->left, level + 1, '\\');
    }
}