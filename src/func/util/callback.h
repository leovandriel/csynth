//
// callback.h - Func that is defined by a regular function.
//
// `callback(input, function, context)`
//
#ifndef CSYNTH_CALLBACK_H
#define CSYNTH_CALLBACK_H

#include <assert.h>
#include <stdio.h>
#include <math.h>

#include "../../core/func.h"
#include "../gen/const.h"

typedef struct
{
    double (*callback)(Gen **, int, double, void *);
    void *context;
} CallbackContext;

double callback_eval(Gen **args, __attribute__((unused)) int count, __attribute__((unused)) double delta, void *_context)
{
    CallbackContext *context = (CallbackContext *)_context;
    return context->callback(args, count, delta, context->context);
}

Func *callback_args(double (*callback)(Gen **, int, double, void *), void *context, int count, ...)
{
    CallbackContext initial = (CallbackContext){
        .callback = callback,
        .context = context};
    va_list valist;
    va_start(valist, count);
    Func *func = func_create_va(NULL, callback_eval, NULL, sizeof(CallbackContext), &initial, count, valist);
    va_end(valist);
    return func;
}

#define callback(_callback, _context, ...) (callback_args(_callback, _context, (sizeof((Func *[]){__VA_ARGS__}) / sizeof(Func **)), __VA_ARGS__))

double test_callback_add(Gen **args, int count, double delta, void *context)
{
    assert(count == 2);
    assert(delta == 0.1);
    assert(*(int *)context == 2);
    return gen_eval(args[0]) + gen_eval(args[1]);
}

void test_callback()
{
    int context = 2;
    func t = callback(test_callback_add, &context, _(3), _(4));
    Gen *g = gen_create(t, 0.1);
    assert(gen_eval(g) == 7);
}

#endif // CSYNTH_CALLBACK_H
