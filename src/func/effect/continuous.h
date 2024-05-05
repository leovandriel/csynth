//
// continuous.h - Prevents its input from being reset
//
// Funcs can call `gen_reset` on their input to revert the state, e.g. in `loop`
// to allow for looping. The `continuous` func prevents the propagation of such
// a reset, allowing the func argument to continue independently of such a loop.
// This allows for combining looped and non-looped funcs in cases where nesting
// is required. See `dynamic.c` for an example.
//
// `continuous(input)`
//
#ifndef CSYNTH_CONTINUOUS_H
#define CSYNTH_CONTINUOUS_H

#include "../../util/test.h"
#include "../../core/func.h"
#include "./loop.h"
#include "../env/envs.h"

double continuous_eval(__attribute__((unused)) int count, Gen **args, __attribute__((unused)) double delta, __attribute__((unused)) void *context);
// implemented in func.h

Func *continuous(Func *input)
{
    return func_create(NULL, continuous_eval, NULL, 0, NULL, 1, input);
}

void test_continuous()
{
    Func *t = loop_(continuous(linear_(0, 1, 1)), 2);
    Gen *g = gen_create(t, 1);
    assert_gen_equal(g, 0);
    assert_gen_equal(g, 1);
    assert_gen_equal(g, 2);
    assert_gen_equal(g, 3);
    assert_gen_equal(g, 4);
}

#endif // CSYNTH_CONTINUOUS_H
