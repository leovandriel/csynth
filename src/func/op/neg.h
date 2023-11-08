//
// neg.h - Negate function
//
// `neg(value)` returns -value.
//
#ifndef CSYNTH_NEG_H
#define CSYNTH_NEG_H

#include <assert.h>

#include "../../core/func.h"
#include "../gen/const.h"

static double neg_eval(__attribute__((unused)) int count, Gen **args, __attribute__((unused)) double delta, __attribute__((unused)) void *context)
{
    double output = gen_eval(args[0]);
    return -output;
}

Func *neg(Func *value)
{
    return func_create(NULL, neg_eval, NULL, 0, NULL, 1, value);
}

void test_neg()
{
    assert(gen_eval(gen_create(neg(const_(1)), .1)) == -1.0);
    assert(gen_eval(gen_create(neg(const_(-2)), .1)) == 2.0);
}

#endif // CSYNTH_NEG_H
