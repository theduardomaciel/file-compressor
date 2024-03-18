#include <stdio.h>

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include "priority_queue.h"

#ifndef PRIORITY_QUEUE_TEST
#define PRIORITY_QUEUE_TEST

void pq_init_test();

void pq_enqueue_test();

void pq_dequeue_test();

void pq_destroy_test();

#endif // PRIORITY_QUEUE_TEST