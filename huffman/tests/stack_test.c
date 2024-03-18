#include "stack_test.h"

void stack_init_test(void)
{
    stack *s = stack_init();

    CU_ASSERT_PTR_NOT_NULL(s);
    CU_ASSERT_PTR_NULL(s->top);
    CU_ASSERT_EQUAL(s->size, 0);

    stack_destroy(s);
}

void stack_push_test(void)
{
    stack *s = stack_init();

    stack_push(s, 1);
    CU_ASSERT_EQUAL(s->top->data, 1);
    CU_ASSERT_PTR_NULL(s->top->next);
    CU_ASSERT_EQUAL(s->size, 1);

    stack_push(s, 2);
    CU_ASSERT_EQUAL(s->top->data, 2);
    CU_ASSERT_EQUAL(s->top->next->data, 1);
    CU_ASSERT_EQUAL(s->size, 2);

    stack_destroy(s);
}

void stack_pop_test(void)
{
    stack *s = stack_init();

    stack_push(s, 1);
    stack_push(s, 2);
    stack_push(s, 3);

    CU_ASSERT_EQUAL(stack_pop(s), 3);
    CU_ASSERT_EQUAL(s->size, 2);

    CU_ASSERT_EQUAL(stack_pop(s), 2);
    CU_ASSERT_EQUAL(s->size, 1);

    CU_ASSERT_EQUAL(stack_pop(s), 1);
    CU_ASSERT_EQUAL(s->size, 0);

    CU_ASSERT_PTR_NULL(s->top);

    stack_destroy(s);
}

void stack_copy_test(void)
{
    stack *s = stack_init();

    stack_push(s, 1);
    stack_push(s, 2);
    stack_push(s, 3);

    stack *copy = stack_copy(s);

    CU_ASSERT_EQUAL(copy->size, 3);
    CU_ASSERT_EQUAL(stack_pop(copy), 3);
    CU_ASSERT_EQUAL(stack_pop(copy), 2);
    CU_ASSERT_EQUAL(stack_pop(copy), 1);

    stack_destroy(s);
    stack_destroy(copy);
}

void stack_destroy_test(void)
{
    stack *s = stack_init();

    stack_push(s, 1);
    stack_push(s, 2);
    stack_push(s, 3);

    stack_destroy(s);
    CU_ASSERT_PTR_NULL(s);
}