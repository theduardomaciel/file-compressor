#include "huffman_tree_test.h"

void huffman_tree_init_test(void)
{
    huffman_node *ht = ht_init();

    CU_ASSERT_PTR_NOT_NULL(ht);
    CU_ASSERT_PTR_NULL(ht->data);
    CU_ASSERT_EQUAL(ht->frequency, 0);
    CU_ASSERT_PTR_NULL(ht->left);
    CU_ASSERT_PTR_NULL(ht->right);

    ht_destroy(ht);
}

void ht_create_node_test(void)
{
    uint8_t data = 'a';
    huffman_node *node = ht_create_node((void *)&data, 0, NULL, NULL);

    CU_ASSERT_PTR_NOT_NULL(node);
    CU_ASSERT_EQUAL(*(uint8_t *)node->data, 'a');
    CU_ASSERT_EQUAL(node->frequency, 0);
    CU_ASSERT_PTR_NULL(node->left);
    CU_ASSERT_PTR_NULL(node->right);

    ht_destroy(node);
}

void is_leaf_test(void)
{
    uint8_t data = 'a';
    huffman_node *node = ht_create_node((void *)&data, 0, NULL, NULL);

    CU_ASSERT_EQUAL(is_leaf(node), 1);

    ht_destroy(node);
}

void is_scaped_char_test(void)
{
    uint8_t data = 'a';
    huffman_node *node = ht_create_node((void *)&data, 0, NULL, NULL);

    CU_ASSERT_EQUAL(is_scaped_char(node), 0);

    ht_destroy(node);
}

void ht_get_tree_size_test(void)
{
    uint8_t data = 'a';
    huffman_node *node = ht_create_node((void *)&data, 0, NULL, NULL);

    CU_ASSERT_EQUAL(ht_get_tree_size(node), 1);

    ht_destroy(node);
}

void ht_pre_order_test(void)
{
    uint8_t data = 'a';
    huffman_node *node = ht_create_node((void *)&data, 0, NULL, NULL);

    print_pre_order(node);

    ht_destroy(node);
}

void ht_destroy_test(void)
{
    uint8_t data = 'a';
    huffman_node *node = ht_create_node((void *)&data, 0, NULL, NULL);

    ht_destroy(node);

    CU_ASSERT_PTR_NULL(node);
}

int compare_huffman_nodes(const void *a, const void *b)
{
    huffman_node *node_a = (huffman_node *)a;
    huffman_node *node_b = (huffman_node *)b;

    if (node_a->frequency < node_b->frequency)
    {
        return -1;
    }
    else if (node_a->frequency > node_b->frequency)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void build_huffman_tree_test(void)
{
    uint8_t data = 'a';
    huffman_node *node = ht_create_node((void *)&data, 0, NULL, NULL);

    priority_queue *pq = pq_init(10, compare_huffman_nodes);
    pq_push(pq, node);

    huffman_node *ht = build_huffman_tree(pq);

    CU_ASSERT_PTR_NOT_NULL(ht);
    CU_ASSERT_PTR_NULL(ht->data);
    CU_ASSERT_EQUAL(ht->frequency, 0);
    CU_ASSERT_PTR_NOT_NULL(ht->left);
    CU_ASSERT_PTR_NOT_NULL(ht->right);

    ht_destroy(ht);
    pq_destroy(pq);
}

void rebuild_huffman_tree_test(void)
{
    // Testamos com a árvore em pré-ordem dos slides: **CB***FEDA
    char *preorder_tree_string = "**CB***FEDA";
    uint8_t preorder_tree[11];

    for (int i = 0; i < 11; i++)
    {
        preorder_tree[i] = preorder_tree_string[i];
    }

    huffman_node *tree = reconstruct_tree(preorder_tree);

    CU_ASSERT_EQUAL(*(uint8_t *)tree->data, '*');
    CU_ASSERT_EQUAL(*(uint8_t *)tree->right->data, '*');
    CU_ASSERT_EQUAL(*(uint8_t *)tree->left->left->data, 'C');
    CU_ASSERT_EQUAL(*(uint8_t *)tree->left->right->data, 'B');
    CU_ASSERT_EQUAL(*(uint8_t *)tree->right->right->data, 'A');
    CU_ASSERT_EQUAL(*(uint8_t *)tree->right->left->right->data, 'D');
    CU_ASSERT_EQUAL(*(uint8_t *)tree->right->left->left->left->data, 'F');
}