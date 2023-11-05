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
