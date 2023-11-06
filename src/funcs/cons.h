//
// cons.h - A constant value function.
//
// `cons(value)` takes one value, which it will return during sampling. Primary
// purpose is wrapping doubles in a Func, so it can be used as argument for
// other functions.
//
// For convenience, the macro `_(value)` is provided, which is equal to
// `cons(value)`.
// - ZERO - A constant function, which always returns 0
// - ONE - A constant function, which always returns 1
//
#ifndef COMPOSER_CONS_H
#define COMPOSER_CONS_H

#include <assert.h>

#include "../core/func.h"

typedef struct
{
    double value;
} ConsContext;

double cons_eval(__attribute__((unused)) Gen **args, __attribute__((unused)) int count, __attribute__((unused)) double delta, void *_context)
{
    ConsContext *context = (ConsContext *)_context;
    return context->value;
}

Func *cons(double value)
{
    ConsContext initial = (ConsContext){
        .value = value,
    };
    return func_create(NULL, cons_eval, NULL, sizeof(ConsContext), &initial, 0);
}

#define _(...) cons(__VA_ARGS__)
#define ZERO cons(0.0)
#define ONE cons(1.0)

void test_cons()
{
    assert(gen_eval(gen_create(cons(1), .1)) == 1.0);
    assert(gen_eval(gen_create(cons(-2), .1)) == -2.0);
}

#endif // COMPOSER_CONS_H
