//
// neg.h - Negate function
//
// `neg(value)` returns -value.
//
#ifndef COMPOSER_NEG_H
#define COMPOSER_NEG_H

#include "../core/func.h"

double neg_eval(Gen **args, __attribute__((unused)) int count, __attribute__((unused)) double delta, __attribute__((unused)) void *context)
{
    double output = gen_eval(args[0]);
    return -output;
}

Func *neg(Func *value)
{
    return func_create(NULL, neg_eval, NULL, 0, NULL, 1, value);
}

#define sub(a, b) add(a, neg(b))

#endif // COMPOSER_NEG_H
