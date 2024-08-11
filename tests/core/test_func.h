#include "../../src/core/func.h"
#include "../util/test.h"

int test_init_callback(__U size_t count, __U Gen **args, __U void *context)
{
    return 0;
}

double test_eval_callback(__U size_t count, __U Gen **args, __U Eval *eval, __U void *context)
{
    return 0.0;
}

void test_free_callback(__U size_t count, __U void *context)
{
    // noop
}

void test_cleanup_callback(__U void *initial)
{
    // noop
}

void test_empty(void)
{
    Func *func = func_create_name("test_name", NULL, NULL, NULL, NULL, 0, NULL, FuncFlagNone, 0, (Func *[]){}, "test_args");
    assert_null(func->args);
    assert_long_equal(func->count, 0);
    assert_long_equal(func->size, 0);
    assert_null(func->initial);
    assert_null(func->init_cb);
    assert_null(func->eval_cb);
    assert_null(func->free_cb);
    assert_long_equal(func->flags, 0);
    assert_null(func->next);
    assert_string_equal(func->name, "test_name");
    assert_string_equal(func->arg_names, "test_args");
    func_free();
}

void test_full(void)
{
    int context = 42;
    Func *input = func_create_name("input_name", NULL, NULL, NULL, NULL, 0, NULL, FuncFlagNone, 0, (Func *[]){}, "input_args");
    Func *func = func_create_name("test_name", test_init_callback, test_eval_callback, test_free_callback, test_cleanup_callback, sizeof(int), &context, FuncFlagStopReset | FuncFlagSkipReset, 1, (Func *[]){input}, "test_args");
    assert_not_null(func->args);
    assert_long_equal(func->count, 1);
    assert_long_equal(func->size, sizeof(int));
    assert_ptr_equal(func->args[0], input);
    assert_ptr_unequal(func->initial, &context);
    assert_long_equal(*(int *)func->initial, context);
    assert_ptr_equal(func->init_cb, test_init_callback);
    assert_ptr_equal(func->eval_cb, test_eval_callback);
    assert_ptr_equal(func->free_cb, test_free_callback);
    assert_long_equal(func->flags, FuncFlagStopReset | FuncFlagSkipReset);
    assert_ptr_equal(func->next, input);
    assert_string_equal(func->name, "test_name");
    assert_string_equal(func->arg_names, "test_args");
    func_free();
}

void test_func(void)
{
    test_empty();
    test_full();
}
