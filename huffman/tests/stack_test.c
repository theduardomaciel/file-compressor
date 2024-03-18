#include "stack_test.h"

void stack_test_init(void)
{
    stack *s = stack_init();

    CU_ASSERT_PTR_NOT_NULL(s);
    CU_ASSERT_PTR_NULL(s->top);
    CU_ASSERT_EQUAL(s->size, 0);

    stack_destroy(s);
}