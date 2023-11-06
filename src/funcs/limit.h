//
// limit.h - Limits the delta between successive samples
//
// `limit(input, limit)` with input and limit functions and limit the amplitude
// delta. This can be used to prevent clicks and pops.
//
#ifndef COMPOSER_LIMIT_H
#define COMPOSER_LIMIT_H

#include <assert.h>

#include "../core/func.h"
#include "./cons.h"
#include "./square.h"

typedef struct
{
    double output;
} LimitContext;

double limit_eval(Gen **args, __attribute__((unused)) int count, double delta, void *_context)
{
    LimitContext *context = (LimitContext *)_context;
    double input = gen_eval(args[0]);
    double limit = gen_eval(args[1]) * delta;
    if (input < context->output - limit)
    {
        input = context->output - limit;
    }
    else if (input > context->output + limit)
    {
        input = context->output + limit;
    }
    context->output = input;
    return input;
}

Func *limit(Func *input, Func *limit)
{
    return func_create(NULL, limit_eval, NULL, sizeof(LimitContext), NULL, 2, input, limit);
}

void test_limit()
{
    func t = limit(square(cons(1)), cons(3));
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

#endif // COMPOSER_LIMIT_H
