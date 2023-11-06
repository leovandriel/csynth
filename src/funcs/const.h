//
// const.h - A constant value function.
//
// `const_(value)` takes one value, which it will return during sampling. Primary
// purpose is wrapping doubles in a Func, so it can be used as argument for
// other functions.
//
// For convenience, the macro `_(value)` is provided, which is equal to
// `const_(value)`.
// - ZERO - A constant function, which always returns 0
// - ONE - A constant function, which always returns 1
//
#ifndef CSYNTH_CONST_H
#define CSYNTH_CONST_H

#include <assert.h>

#include "../core/func.h"

typedef struct
{
    double value;
} ConstContext;

double const_eval(__attribute__((unused)) Gen **args, __attribute__((unused)) int count, __attribute__((unused)) double delta, void *_context)
{
    ConstContext *context = (ConstContext *)_context;
    return context->value;
}

Func *const_(double value)
{
    ConstContext initial = (ConstContext){
        .value = value,
    };
    return func_create(NULL, const_eval, NULL, sizeof(ConstContext), &initial, 0);
}

#define _(...) (const_(__VA_ARGS__))
#define ZERO (const_(0.0))
#define ONE (const_(1.0))

void test_const()
{
    assert(gen_eval(gen_create(const_(1), .1)) == 1.0);
    assert(gen_eval(gen_create(const_(-2), .1)) == -2.0);
}

#endif // CSYNTH_CONST_H
