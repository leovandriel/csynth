//
// add.h - Addition function
//
// `add(...)` returns the sum of a list of functions.
//
#ifndef CSYNTH_ADD_H
#define CSYNTH_ADD_H

#include <stdarg.h>

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../gen/const.h"

static double add_eval(int count, Gen **args, Eval eval, __U void *context)
{
    double sum = 0;
    for (int i = 0; i < count; i++)
    {
        sum += gen_eval(args[i], eval);
    }
    return sum;
}

Func *add_array(int count, Func **args)
{
    return func_create_array(NULL, add_eval, NULL, 0, NULL, FuncFlagNone, count, args);
}

#define add(...) (add_array(FUNCS(__VA_ARGS__)))

Func *add_(Func *input, double diff)
{
    return add(input, const_(diff));
}

#endif // CSYNTH_ADD_H
