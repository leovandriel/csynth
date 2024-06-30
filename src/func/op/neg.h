//
// neg.h - Negate function
//
// `neg(value)` returns -value.
//
#ifndef CSYNTH_NEG_H
#define CSYNTH_NEG_H

#include "../../core/func.h"
#include "../../core/gen.h"

static double neg_eval(__U int count, Gen **args, Eval eval, __U void *context)
{
    double output = gen_eval(args[0], eval);
    return -output;
}

Func *neg(Func *input)
{
    return func_create(NULL, neg_eval, NULL, 0, NULL, FuncFlagNone, FUNCS(input));
}

#endif // CSYNTH_NEG_H
