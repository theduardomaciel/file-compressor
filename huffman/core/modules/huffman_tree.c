#include "priority_queue.h"
#include "huffman_tree.h"
#include "utils.h"

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
    stack *stack = stack_init();
    stack_push(stack, root);

    while (stack->size != 0)
    {
        huffman_node *current_node = (huffman_node *)stack_pop(stack);

        // Se o nó atual não for um nó interno, mas sim uma folha, precisamos 'escapar' o caractere
        // Fazemos isso para que seja possível distingui-lo de um nó interno comum
        if (is_leaf(current_node) && is_scaped_char(current_node))
        {
            // Realizamos a chamada da função de callback com um ponteiro para o caractere '\'
            // pois a função callback espera um ponteiro genérico (void *) como argumento.
            // Dessa forma, o operador '&' é usado para obter o endereço de memória onde o caractere
            // está armazenado, permitindo que seja passado corretamente para a função callback.
            callback(&(char){'\\'}, arg);
        }

        // Caso não, podemos chamar o callback com o caractere normal
        callback(current_node->data, arg);

        // Empilhar os ramos direito e esquerdo, se existirem
        if (current_node->right != NULL)
        {
            stack_push(stack, current_node->right);
        }
        if (current_node->left != NULL)
        {
            stack_push(stack, current_node->left);
        }
    }

    // Liberar a memória usada pela pilha
    stack_destroy(stack);
}

huffman_node *build_huffman_tree(priority_queue *queue)
{
    NULL_POINTER_CHECK(queue);

    // Garantimos que ainda existem nós na fila
    while (queue->size > 1)
    {
        // printf("Tamanho da fila: %lu\n", queue->size);

        // Desempilhamos os dois nós com menores frequências
        huffman_node *left = (huffman_node *)pq_dequeue(queue);
        huffman_node *right = (huffman_node *)pq_dequeue(queue);

        // Seguindo as especificações do projeto, o nó pai terá um caractere nulo (asterisco)
        // Por estarmos utilizando um ponteiro para void, precisamos alocar memória para o caractere
        void *parent_data = malloc(sizeof(uint8_t));
        *(uint8_t *)parent_data = '*';

        uint64_t summed_frequencies = left->frequency + right->frequency;
        // Criamos um novo nó com os dois nós desempilhados como filhos

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

void build_bytes_dictionary(huffman_node *root, stack **bytes_dictionary, stack *current_path)
{
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

// Nós internos sempre serão representados por um *, no entanto, para diferenciá-lo de uma folha, precisamos 'escapar' o caractere
// Para isso, utilizamos o caractere '\' antes do '*', indicando que o próximo caractere representa uma folha
huffman_node *rebuild_huffman_tree(uint8_t **header_tree)
{
    // Alocamos espaço para armazenar o símbolo atual da árvore
    uint8_t *item = malloc(sizeof(uint8_t));
    uint8_t *current_symbol = *header_tree; // Obtém o símbolo atual da árvore

    // Obs.: Ao utilizar (*header_tree)++ estamos avançando para o próximo símbolo

    // Se o símbolo atual for '*', indica um nó interno
    if (*current_symbol == '*')
    {
        *item = '*';
        (*header_tree)++;

        // Reconstruímos as subárvores esquerda e direita recursivamente
        huffman_node *left = rebuild_huffman_tree(header_tree);
        huffman_node *right = rebuild_huffman_tree(header_tree);

        // Criamos um nó com as subárvores esquerda e direita
        return ht_create_node((void *)item, 0, left, right);
    }
    else
    {
        // Se o símbolo atual for '\', indica que o próximo símbolo é um caractere especial,
        // portanto, avançamos para o próximo símbolo e o armazenamos em item
        if (*current_symbol == '\\')
        {
            (*header_tree)++;
            *item = **header_tree;
            (*header_tree)++;
        }
        else
        {
            // Caso contrário, o símbolo atual é um caractere normal, então o armazenamos em item e avançamos para o próximo símbolo
            *item = *current_symbol;
            (*header_tree)++;
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
