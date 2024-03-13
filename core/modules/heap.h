#ifndef HEAP_H
#define HEAP_H

// Estrutura para representar um nó de uma MinHeap
typedef struct
{
    void *value;
    unsigned frequency;
    struct heap_node *left, *right;
} heap_node;

// Estrutura para representar uma MinHeap
typedef struct
{
    unsigned size;
    unsigned capacity;
    heap_node **nodes;
} heap;

/**
 * Cria um novo heap com a capacidade especificada.
 *
 * @param capacity A capacidade do heap.
 * @return Um ponteiro para o heap criado.
 */
heap *create_heap(unsigned capacity);

/**
 * Cria um novo nó de heap com o valor e a frequência especificados.
 *
 * @param value O valor do nó.
 * @param frequency A frequência do nó.
 * @return Um ponteiro para o nó de heap criado.
 */
heap_node *new_heap_node(char value, unsigned frequency);

/**
 * Troca os ponteiros de dois nós da heap.
 *
 * @param a Ponteiro para o primeiro nó.
 * @param b Ponteiro para o segundo nó.
 */
void swap_nodes(heap_node **a, heap_node **b);

/**
 * Mantém a propriedade de heap mínima a partir de um determinado índice.
 *
 * @param h Ponteiro para a heap.
 * @param index Índice a partir do qual a propriedade de heap mínima deve ser mantida.
 */
void min_heapify(heap *h, int index);

/**
 * Extrai o nó mínimo da heap.
 *
 * @param h Ponteiro para a heap.
 * @return Ponteiro para o nó mínimo extraído.
 */
heap_node *extract_min(heap *h);

/**
 * Insere um nó na heap mínima.
 *
 * @param h Ponteiro para a heap.
 * @param node Ponteiro para o nó a ser inserido.
 */
void insert_min_heap(heap *h, heap_node *node);

/**
 * Constrói uma heap mínima a partir de uma heap vazia.
 *
 * @param h Ponteiro para a heap.
 */
void build_min_heap(heap *h);

/**
 * Verifica se a heap possui tamanho igual a um.
 *
 * @param h Ponteiro para a heap.
 * @return 1 se a heap possui tamanho igual a um, 0 caso contrário.
 */
int is_size_one(heap *h);

/**
 * Cria e constrói uma heap mínima a partir de um conjunto de dados e suas frequências.
 *
 * @param data Conjunto de dados.
 * @param frequencies Frequências correspondentes aos dados.
 * @param size Tamanho do conjunto de dados.
 * @return Ponteiro para a heap criada e construída.
 */
heap *create_and_build_min_heap(char *data, int *frequencies, int size);

#endif // HEAP_H