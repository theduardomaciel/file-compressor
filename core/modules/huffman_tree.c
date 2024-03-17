#include "utils.h"
#include "huffman_tree.h"
#include "priority_queue.h"

/*
    ⮕ Funções públicas
    São funções que podem ser acessadas por qualquer arquivo que inclua este arquivo
*/

huffman_node *ht_init()
{
    huffman_node *tree = malloc(sizeof(huffman_node));
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
    return *(uint8_t *)node->data == '\\' || *(uint8_t *)node->data == '*';
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

    if (is_leaf(root) && is_scaped_char(root))
    {
        size++; // E incrementamos o tamanho para este nó caso ele seja uma folha (precisa de um caractere de escape \ pra ser identificado corretamente)
    }

    // Em seguida, calculamos o tamanho dos subárvores esquerda e direita recursivamente
    size += ht_get_tree_size(root->left);
    size += ht_get_tree_size(root->right);

    return size;
}

void ht_pre_order(huffman_node *root, void (*callback)(void *data, void *arg), void *arg)
{
    if (root != NULL)
    {
        // Se o nó atual não for um nó interno, mas sim uma folha, precisamos 'escapar' o caractere
        if (is_leaf(root) && is_scaped_char(root))
        {
            // É necessário declarar uma variável pois não podemos passar o valor diretamente para a função
            char escape = '\\';
            callback(&escape, arg);
        }

        // Caso não, podemos chamar o callback com o caractere normal
        callback(root->data, arg);

        // Em por fim, chamamos a função recursivamente para os ramos esquerdo e direito da árvore
        ht_pre_order(root->left, callback, arg);
        ht_pre_order(root->right, callback, arg);
    }
}

int compare(const void *d1, const void *d2)
{
    huffman_node *n1 = (huffman_node *)d1;
    huffman_node *n2 = (huffman_node *)d2;

    if (n1->frequency == n2->frequency)
    {
        return 1; // não pode ser 0 pois causa ambiguidade
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

priority_queue *build_frequency_queue(uint64_t *frequency_table)
{
    priority_queue *queue = init_priority_queue(MAX_SIZE, compare);

    // Adiciona todos os bytes que aparecem no arquivo (têm frequência maior que 0) na fila de prioridade
    for (uint16_t i = 0; i < MAX_SIZE; i++)
    {
        uint16_t current_frequency = frequency_table[i];

        if (current_frequency > 0)
        {
            uint8_t *data = malloc(sizeof(uint8_t));
            NULL_POINTER_CHECK(data);

            *data = i;

            // printf("Enfileirando %d (%d)\n", i, current_frequency);
            pq_enqueue(queue, ht_create_node(data, current_frequency, NULL, NULL));
        }
    }

    // pq_print(queue);

    return queue;
}

huffman_node *build_huffman_tree(priority_queue *queue)
{
    NULL_POINTER_CHECK(queue);

    // Quando alcançarmos o último elemento, estamos tratando da raiz da árvore
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

            /* printf("🖇️  Unindo os dois nós com menores frequências:\n");
            printf("\t\tNó pai: %c (%ld)\n", *(uint8_t *)parent_data, summed_frequencies);
            printf("\t\t/\t\\\n");
            printf("Nó esquerdo: %c (%ld)\t", *(uint8_t *)left->data, left->frequency);
            printf("Nó direito: %c (%ld)\n", *(uint8_t *)right->data, right->frequency);
            printf("--------------------\n"); */

            pq_enqueue(queue, ht_create_node(parent_data, summed_frequencies, left, right));
        }

        return (huffman_node *)pq_dequeue(queue);
    }
}

void build_bytes_dictionary(huffman_node *root, stack *bytes_dictionary[MAX_SIZE], stack *current_path)
{
    // Condição de parada: quando não houverem nós para explorar
    if (root != NULL)
    {
        // Se tivermos chegado a uma folha, copiamos o caminho até ela para o dicionário
        if (is_leaf(root))
        {
            stack *new_path = stack_copy(current_path);
            bytes_dictionary[*(uint8_t *)root->data] = new_path; // utilizamos o byte correspondente ao nó como índice no dicionário
        }
        else
        {
            // Se não tivermos chegado a uma folha, precisamos continuar a percorrer a árvore

            // Primeiro, empurramos um novo bit para o byte atual. Se estiver percorrendo a esquerda, empurramos 0, caso contrário, 1
            // Em seguida, chamamos a função recursivamente para o ramo da árvore, o que repete o processo até encontrar uma folha
            // Depois de explorar o ramo completamente, desempilhamos o bit adicionado
            // Isso nos permite voltar um nível na árvore e explorar o outro ramo

            stack_push(current_path, malloc(sizeof(uint8_t)));
            *(uint8_t *)current_path->top->data = 0;

            build_bytes_dictionary(root->left, bytes_dictionary, current_path);
            stack_pop(current_path);

            stack_push(current_path, malloc(sizeof(uint8_t)));
            *(uint8_t *)current_path->top->data = 1;

            build_bytes_dictionary(root->right, bytes_dictionary, current_path);
            stack_pop(current_path);
        }
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

    priority_queue *pq_copy = init_priority_queue(pq->capacity, pq->comparator);

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

void print_dictionary(stack *paths_of_bytes[MAX_SIZE])
{
    for (int i = 0; i < 256; i++)
    {
        stack *current_path = paths_of_bytes[i];
        if (current_path != NULL && current_path->top != NULL)
        {
            // Imprime os bytes em hexadecimal
            printf("Byte 0x%02X: ", i);

            stack_node *current = current_path->top;

            while (current != NULL)
            {
                printf("%d", *(uint8_t *)current->data);
                current = current->next;
            }

            printf("\n");
        }
    }
}
