#include <unistd.h>

#include "../../src/util/worker.h"
#include "./test.h"

size_t test_called = 0;
size_t test_context = 0;

void test_callback(void *context)
{
    test_called++;
    test_context = *(int *)context;
}

void test_worker(void)
{
    Worker worker;
    int context = 3;
    worker_init(&worker);
    worker_run(&worker, test_callback, &context);
    sleep(1);
    assert_long_equal(test_called, 1);
    assert_long_equal(test_context, 3);
    worker_run(&worker, test_callback, &context);
    sleep(1);
    assert_long_equal(test_called, 2);
    worker_free(&worker);
}
