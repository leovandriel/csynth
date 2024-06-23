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

static double add_eval(int count, Gen **args, __U double delta, __U void *context)
{
    double sum = 0;
    for (int i = 0; i < count; i++)
    {
        sum += gen_eval(args[i]);
    }
    return sum;
}

Func *add_args(int count, ...)
{
    va_list valist = {0};
    va_start(valist, count);
    Func *func = func_create_va(NULL, add_eval, NULL, 0, NULL, FUNC_FLAG_DEFAULT, count, valist);
    va_end(valist);
    return func;
}

#define add(...) (add_args((sizeof((Func *[]){__VA_ARGS__}) / sizeof(Func **)), __VA_ARGS__))

Func *add_(Func *input, double diff)
{
    return add(input, const_(diff));
}

Func *add_array(int count, Func **args)
{
    return func_create_array(NULL, add_eval, NULL, 0, NULL, FUNC_FLAG_DEFAULT, count, args);
}

#endif // CSYNTH_ADD_H
