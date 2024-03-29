//
// callback.h - Func that is defined by a regular function.
//
// `callback(input, function, context)`
//
#ifndef CSYNTH_CALLBACK_H
#define CSYNTH_CALLBACK_H

#include <stdio.h>

#include "../../util/test.h"
#include "../../core/func.h"
#include "../gen/const.h"

typedef struct
{
    double (*callback)(int, Gen **, double, void *);
    void *context;
} CallbackContext;

static double callback_func_eval(__attribute__((unused)) int count, __attribute__((unused)) Gen **args, __attribute__((unused)) double delta, void *context_)
{
    CallbackContext *context = (CallbackContext *)context_;
    return context->callback(count, args, delta, context->context);
}

Func *callback_func_args(double (*callback)(int, Gen **, double, void *), void *context, int count, ...)
{
    CallbackContext initial = (CallbackContext){
        .callback = callback,
        .context = context};
    va_list valist;
    va_start(valist, count);
    Func *func = func_create_va(NULL, callback_func_eval, NULL, sizeof(CallbackContext), &initial, count, valist);
    va_end(valist);
    return func;
}

#define callback_func(_callback, _context, ...) (callback_func_args(_callback, _context, (sizeof((Func *[]){__VA_ARGS__}) / sizeof(Func **)), __VA_ARGS__))

typedef struct
{
    double (*callback)(double, double, void *);
    void *context;
} FilterCallbackContext;

static double callback_filter_eval(__attribute__((unused)) int count, Gen **args, __attribute__((unused)) double delta, void *context_)
{
    FilterCallbackContext *context = (FilterCallbackContext *)context_;
    return context->callback(gen_eval(args[0]), delta, context->context);
}

Func *callback_filter(Func *input, double (*callback)(double, double, void *), void *context)
{
    FilterCallbackContext initial = (FilterCallbackContext){
        .callback = callback,
        .context = context};
    return func_create(NULL, callback_filter_eval, NULL, sizeof(FilterCallbackContext), &initial, 1, input);
}

typedef struct
{
    double (*callback)(double, void *);
    void *context;
} GenCallbackContext;

static double callback_gen_eval(__attribute__((unused)) int count, __attribute__((unused)) Gen **args, __attribute__((unused)) double delta, void *context_)
{
    GenCallbackContext *context = (GenCallbackContext *)context_;
    return context->callback(delta, context->context);
}

Func *callback_gen(__attribute__((unused)) Func *input, double (*callback)(double, void *), void *context)
{
    GenCallbackContext initial = (GenCallbackContext){
        .callback = callback,
        .context = context};
    return func_create(NULL, callback_gen_eval, NULL, sizeof(GenCallbackContext), &initial, 0);
}

static double test_callback_add(int count, Gen **args, double delta, void *context)
{
    assert_long_equal(count, 2);
    assert_double_equal(delta, 0.1);
    assert_long_equal(*(int *)context, 2);
    return gen_eval(args[0]) + gen_eval(args[1]);
}

void test_callback()
{
    int context = 2;
    Func *t = callback_func(test_callback_add, &context, const_(3), const_(4));
    Gen *g = gen_create(t, 0.1);
    assert_gen_equal(g, 7);
}

#endif // CSYNTH_CALLBACK_H
