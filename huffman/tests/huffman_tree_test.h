#include <stdio.h>

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include "huffman_tree.h"
#include "priority_queue.h"

#ifndef HUFFMAN_TREE_TEST
#define HUFFMAN_TREE_TEST

void ht_init_test();

void ht_create_node_test();

void is_leaf_test();

void is_scaped_char_test();

void ht_get_tree_size_test();

void ht_pre_order_test();

void ht_destroy_test();

void build_huffman_tree_test();

void rebuild_huffman_tree_test();

#endif // HUFFMAN_TREE_TEST