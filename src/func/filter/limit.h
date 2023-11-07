//
// limit.h - Limits the delta between successive samples
//
// `limit(input, limit)` with input and limit functions and limit the amplitude
// delta. This can be used to prevent clicks and pops.
//
#ifndef CSYNTH_LIMIT_H
#define CSYNTH_LIMIT_H

#include <assert.h>

#include "../../core/func.h"
#include "../gen/const.h"
#include "../gen/square.h"

typedef struct
{
    double output;
} LimitContext;

static double limit_eval(Gen **args, __attribute__((unused)) int count, double delta, void *_context)
{
    LimitContext *context = (LimitContext *)_context;
    double input = gen_eval(args[0]);
    double diff = gen_eval(args[1]) * delta;
    if (input < context->output - diff)
    {
        input = context->output - diff;
    }
    else if (input > context->output + diff)
    {
        input = context->output + diff;
    }
    context->output = input;
    return input;
}

Func *limit(Func *input, Func *diff)
{
    return func_create(NULL, limit_eval, NULL, sizeof(LimitContext), NULL, 2, input, diff);
}

Func *limit_(Func *input, double diff) { return limit(input, const_(diff)); }

void test_limit()
{
    Func *t = limit(square(const_(1)), const_(3));
    Gen *g = gen_create(t, 0.1);
    double epsilon = 1e-9;
    assert(fabs(gen_eval(g) - 0.300000) < epsilon);
    assert(fabs(gen_eval(g) - 0.600000) < epsilon);
    assert(fabs(gen_eval(g) - 0.900000) < epsilon);
    assert(fabs(gen_eval(g) - 1.000000) < epsilon);
    assert(fabs(gen_eval(g) - 1.000000) < epsilon);
    assert(fabs(gen_eval(g) - 0.700000) < epsilon);
    assert(fabs(gen_eval(g) - 0.400000) < epsilon);
    assert(fabs(gen_eval(g) - 0.100000) < epsilon);
    assert(fabs(gen_eval(g) - -0.200000) < epsilon);
    assert(fabs(gen_eval(g) - -0.500000) < epsilon);
    assert(fabs(gen_eval(g) - -0.200000) < epsilon);
    assert(fabs(gen_eval(g) - 0.100000) < epsilon);
}

#endif // CSYNTH_LIMIT_H
