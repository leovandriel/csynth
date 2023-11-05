//
// cons.h - A constant value function.
//
// `cons(value)` takes one value, which it will return during sampling. Primary
// purpose is wrapping doubles in a Func, so it can be used as argument for
// other functions.
//
// For convenience, the macro `_(value)` is provided, which is equal to
// `cons(value)`.
//
#ifndef COMPOSER_CONS_H
#define COMPOSER_CONS_H

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

#endif // COMPOSER_CONS_H
