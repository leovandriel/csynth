//
// mul.h - Multiplication function
//
// `mul(a, b)` returns the product of a list of functions.
//
#ifndef CSYNTH_MUL_H
#define CSYNTH_MUL_H

#include <assert.h>
#include <stdarg.h>

#include "../core/func.h"
#include "./const.h"

double mul_eval(Gen **args, int count, __attribute__((unused)) double delta, __attribute__((unused)) void *context)
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
#define mul_(_input, _factor) (mul(_input, const_(_factor)))

void test_mul()
{
    assert(gen_eval(gen_create(mul(const_(1), const_(1)), .1)) == 1.0);
    assert(gen_eval(gen_create(mul(const_(1), const_(2), const_(3)), .1)) == 6.0);
    assert(gen_eval(gen_create(mul(const_(1)), .1)) == 1.0);
}

#endif // CSYNTH_MUL_H
