//
// max.h - Max function
//
// `max(...)` returns the maximum of the input functions.
//
#ifndef CSYNTH_MAX_H
#define CSYNTH_MAX_H

#include <assert.h>
#include <float.h>
#include <stdarg.h>

#include "../core/func.h"
#include "./cons.h"

double max_eval(Gen **args, int count, __attribute__((unused)) double delta, __attribute__((unused)) void *context)
{
    double max = -FLT_MAX;
    for (int i = 0; i < count; i++)
    {
        double f = gen_eval(args[i]);
        if (max < f)
        {
            max = f;
        }
    }
    return max;
}

Func *max_args(int count, ...)
{
    va_list valist;
    va_start(valist, count);
    Func *func = func_create_va(NULL, max_eval, NULL, 0, NULL, count, valist);
    va_end(valist);
    return func;
}

#define max(...) (max_args((sizeof((Func *[]){__VA_ARGS__}) / sizeof(Func **)), __VA_ARGS__))
#define max_(_input, _min) (max(_input, cons(_min)))

void test_max()
{
    assert(gen_eval(gen_create(max(cons(1), cons(2)), .1)) == 2.0);
    assert(gen_eval(gen_create(max(cons(2), cons(1)), .1)) == 2.0);
    assert(gen_eval(gen_create(max(cons(4), cons(2), cons(3)), .1)) == 4.0);
    assert(gen_eval(gen_create(max(cons(1)), .1)) == 1.0);
}

#endif // CSYNTH_MAX_H
