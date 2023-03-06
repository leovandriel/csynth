#ifndef COMPOSER_CONS_H
#define COMPOSER_CONS_H

#include "../core/func.h"

typedef struct
{
    double value;
} ConsContext;

double cons_eval(__attribute__((unused)) unsigned long index, __attribute__((unused)) int rate, __attribute__((unused)) Func **args, __attribute__((unused)) int count, void *_context)
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

#endif // COMPOSER_CONS_H
