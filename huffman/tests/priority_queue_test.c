#include "priority_queue_test.h"

int compare_int(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

void priority_queue_init_test(void)
{
    priority_queue *pq = pq_init(10, compare_int);

    CU_ASSERT_PTR_NOT_NULL(pq);
    CU_ASSERT_EQUAL(pq->capacity, 10);
    CU_ASSERT_EQUAL(pq->size, 0);
    CU_ASSERT_PTR_NULL(pq->data);
    CU_ASSERT_PTR_NOT_NULL(pq->comparator);

    pq_destroy(pq);
}

void priority_queue_enqueue_test(void)
{
    priority_queue *pq = pq_init(10, compare_int);

    int item = 1;
    pq_enqueue(pq, &item);
    CU_ASSERT_EQUAL(pq->size, 1);
    CU_ASSERT_EQUAL(*(int *)pq->data[0], 1);

    item = 2;
    pq_enqueue(pq, &item);
    CU_ASSERT_EQUAL(pq->size, 2);
    CU_ASSERT_EQUAL(*(int *)pq->data[0], 1);
    CU_ASSERT_EQUAL(*(int *)pq->data[1], 2);

    item = 3;
    pq_enqueue(pq, &item);
    CU_ASSERT_EQUAL(pq->size, 3);
    CU_ASSERT_EQUAL(*(int *)pq->data[0], 1);
    CU_ASSERT_EQUAL(*(int *)pq->data[1], 2);
    CU_ASSERT_EQUAL(*(int *)pq->data[2], 3);

    item = 4;
    pq_enqueue(pq, &item);
    CU_ASSERT_EQUAL(pq->size, 4);
    CU_ASSERT_EQUAL(*(int *)pq->data[0], 1);
    CU_ASSERT_EQUAL(*(int *)pq->data[1], 2);
    CU_ASSERT_EQUAL(*(int *)pq->data[2], 3);
    CU_ASSERT_EQUAL(*(int *)pq->data[3], 4);

    pq_destroy(pq);
}

void priority_queue_dequeue_test(void)
{
    priority_queue *pq = pq_init(10, compare_int);

    int item = 1;
    pq_enqueue(pq, &item);
    item = 2;
    pq_enqueue(pq, &item);
    item = 3;
    pq_enqueue(pq, &item);
    item = 4;
    pq_enqueue(pq, &item);

    CU_ASSERT_EQUAL(pq->size, 4);
    CU_ASSERT_EQUAL(*(int *)pq_dequeue(pq), 1);
    CU_ASSERT_EQUAL(pq->size, 3);
    CU_ASSERT_EQUAL(*(int *)pq_dequeue(pq), 2);
    CU_ASSERT_EQUAL(pq->size, 2);
    CU_ASSERT_EQUAL(*(int *)pq_dequeue(pq), 3);
    CU_ASSERT_EQUAL(pq->size, 1);
    CU_ASSERT_EQUAL(*(int *)pq_dequeue(pq), 4);
    CU_ASSERT_EQUAL(pq->size, 0);
    CU_ASSERT_PTR_NULL(pq_dequeue(pq));

    pq_destroy(pq);
}