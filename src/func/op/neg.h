//
// neg.h - Negate function
//
// `neg(value)` returns -value.
//
#ifndef CSYNTH_NEG_H
#define CSYNTH_NEG_H

#include "../../core/func.h"
#include "../../core/gen.h"

static double neg_eval(__U size_t count, Gen **args, Eval *eval, __U void *context)
{
    double input = gen_eval(args[0], eval);
    return -input;
}

Func *neg_create(Func *input)
{
    return func_create(NULL, neg_eval, NULL, 0, NULL, FuncFlagNone, ARGS(input));
}
#endif // CSYNTH_NEG_H
