//
// neg.h - Negate function
//
// `neg(value)` returns -value.
//
#ifndef COMPOSER_NEG_H
#define COMPOSER_NEG_H

#include <assert.h>

#include "../core/func.h"
#include "./cons.h"

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

void test_neg()
{
    assert(gen_eval(gen_create(neg(cons(1)), .1)) == -1.0);
    assert(gen_eval(gen_create(neg(cons(-2)), .1)) == 2.0);
}

#endif // COMPOSER_NEG_H
