#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include "stack_test.h"
#include "huffman_tree_test.h"
#include "priority_queue_test.h"

int IS_POINTER_NULL(void *ptr)
{
    return ptr == NULL;
}

// Precisamos lembrar que em C, para funções principais, 0 indica sucesso e qualquer outro valor indica falha.

int generic_init_suite(void)
{
    return 0;
}

int generic_clean_suite(void)
{
    return 0;
}

CU_ErrorCode stack_test_setup(void)
{
    CU_pSuite test_suit = CU_add_suite("Stack Test Suite", generic_init_suite, generic_clean_suite);
    if (IS_POINTER_NULL(test_suit))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Adicionamos os casos de teste para o módulo de pilha
    CU_pTest init_test_error = CU_add_test(test_suit, "Teste de inicialização da pilha", stack_init_test);

    CU_pTest push_test_error = CU_add_test(test_suit, "Teste de empurrar elementos para a pilha", stack_push_test);

    CU_pTest pop_test_error = CU_add_test(test_suit, "Teste de remover elementos da pilha", stack_pop_test);

    CU_pTest copy_test_error = CU_add_test(test_suit, "Teste de cópia da pilha", stack_copy_test);

    CU_pTest destroy_test_error = CU_add_test(test_suit, "Teste de destruição da pilha", stack_destroy_test);

    if (
        IS_POINTER_NULL(init_test_error) ||
        IS_POINTER_NULL(push_test_error) ||
        IS_POINTER_NULL(pop_test_error) ||
        IS_POINTER_NULL(copy_test_error) ||
        IS_POINTER_NULL(destroy_test_error))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    return CUE_SUCCESS;
}

CU_ErrorCode huffman_tree_test_setup(void)
{
    CU_pSuite test_suit = CU_add_suite("Huffman Tree Test Suite", generic_init_suite, generic_clean_suite);
    if (IS_POINTER_NULL(test_suit))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Adicionamos os casos de teste para o módulo de árvore de Huffman
    CU_pTest init_test_error = CU_add_test(test_suit, "Teste de inicialização da árvore de Huffman", ht_init_test);

    CU_pTest create_node_test_error = CU_add_test(test_suit, "Teste de criação de nó da árvore de Huffman", ht_create_node_test);

    CU_pTest is_leaf_test_error = CU_add_test(test_suit, "Teste de verificação de folha da árvore de Huffman", is_leaf_test);

    CU_pTest is_scaped_char_test_error = CU_add_test(test_suit, "Teste de verificação de caractere de escape da árvore de Huffman", is_scaped_char_test);

    CU_pTest get_tree_size_test_error = CU_add_test(test_suit, "Teste de obtenção do tamanho da árvore de Huffman", ht_get_tree_size_test);

    if (
        IS_POINTER_NULL(init_test_error) ||
        IS_POINTER_NULL(create_node_test_error) ||
        IS_POINTER_NULL(is_leaf_test_error) ||
        IS_POINTER_NULL(is_scaped_char_test_error) ||
        IS_POINTER_NULL(get_tree_size_test_error))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    return CUE_SUCCESS;
}

CU_ErrorCode priority_queue_test_setup(void)
{
    CU_pSuite test_suit = CU_add_suite("Priority Queue Test Suite", generic_init_suite, generic_clean_suite);
    if (IS_POINTER_NULL(test_suit))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Adicionamos os casos de teste para o módulo de fila de prioridade
    CU_pTest init_test_error = CU_add_test(test_suit, "Teste de inicialização da fila de prioridade", pq_init_test);

    CU_pTest enqueue_test_error = CU_add_test(test_suit, "Teste de inserção de elementos na fila de prioridade", pq_enqueue_test);

    CU_pTest dequeue_test_error = CU_add_test(test_suit, "Teste de remoção de elementos da fila de prioridade", pq_dequeue_test);

    if (
        IS_POINTER_NULL(init_test_error) ||
        IS_POINTER_NULL(enqueue_test_error) ||
        IS_POINTER_NULL(dequeue_test_error))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    return CUE_SUCCESS;
}

int main()
{
    if (CU_initialize_registry() != CUE_SUCCESS)
    {
        printf("Erro ao inicializar o registro do CUnit.\n");
        return CU_get_error();
    }

    CU_ErrorCode stack_setup_error = stack_test_setup();
    if (stack_setup_error != CUE_SUCCESS)
    {
        return stack_setup_error;
    }

    CU_ErrorCode huffman_tree_setup_error = huffman_tree_test_setup();
    if (huffman_tree_setup_error != CUE_SUCCESS)
    {
        return huffman_tree_setup_error;
    }

    CU_ErrorCode priority_queue_setup_error = priority_queue_test_setup();
    if (priority_queue_setup_error != CUE_SUCCESS)
    {
        return priority_queue_setup_error;
    }

    CU_basic_run_tests();
    CU_cleanup_registry();

    // Retorna o resultado dos testes
    return CU_get_error();
}