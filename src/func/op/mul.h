//
// mul.h - Multiplication function
//
// `mul(a, b)` returns the product of a list of functions.
//
#ifndef CSYNTH_MUL_H
#define CSYNTH_MUL_H

#include <assert.h>
#include <stdarg.h>

#include "../../core/func.h"
#include "../gen/const.h"

static double mul_eval(Gen **args, int count, __attribute__((unused)) double delta, __attribute__((unused)) void *context)
{
    double output = 1.0;
    for (int i = 0; i < count; i++)
    {
        output *= gen_eval(args[i]);
    }
    return output;
}

Func *mul_args(int count, ...)
{
    va_list valist;
    va_start(valist, count);
    Func *func = func_create_va(NULL, mul_eval, NULL, 0, NULL, count, valist);
    va_end(valist);
    return func;
}

#define mul(...) (mul_args((sizeof((Func *[]){__VA_ARGS__}) / sizeof(Func **)), __VA_ARGS__))

Func *mul_(Func *input, double factor)
{
    return mul(input, const_(factor));
}

Func *mul_array(int count, Func **args)
{
    return func_create_array(NULL, mul_eval, NULL, 0, NULL, count, args);
}

void test_mul()
{
    assert(gen_eval(gen_create(mul(const_(1), const_(1)), .1)) == 1.0);
    assert(gen_eval(gen_create(mul(const_(1), const_(2), const_(3)), .1)) == 6.0);
    assert(gen_eval(gen_create(mul(const_(1)), .1)) == 1.0);
}

#endif // CSYNTH_MUL_H
