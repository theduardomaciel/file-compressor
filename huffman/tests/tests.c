#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include "stack_test.h"

/**
 * Macro de depuração.
 *
 * Verifica se há um ponteiro NULL e imprime a mensagem de erro, o arquivo de origem e
 * linha via 'stderr' .
 * Se a verificação falhar, o programa será encerrado com o código de erro (-1).
 */
void NULL_POINTER_CHECK(void *pointer)
{
    if (pointer == NULL)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
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
    NULL_POINTER_CHECK(test_suit);

    // Adicionamos os casos de teste para o módulo de pilha
    CU_ErrorCode init_test_error = CU_add_test(test_suit, "Teste de inicialização da pilha", stack_init_test);
    NULL_POINTER_CHECK(init_test_error);

    CU_ErrorCode push_test_error = CU_add_test(test_suit, "Teste de empurrar elementos para a pilha", stack_push_test);
    NULL_POINTER_CHECK(push_test_error);

    CU_ErrorCode pop_test_error = CU_add_test(test_suit, "Teste de remover elementos da pilha", stack_pop_test);
    NULL_POINTER_CHECK(pop_test_error);

    CU_ErrorCode copy_test_error = CU_add_test(test_suit, "Teste de cópia da pilha", stack_copy_test);
    NULL_POINTER_CHECK(copy_test_error);

    CU_ErrorCode destroy_test_error = CU_add_test(test_suit, "Teste de destruição da pilha", stack_destroy_test);
    NULL_POINTER_CHECK(destroy_test_error);

    return CUE_SUCCESS;
}