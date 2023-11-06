//
// add.h - Addition function
//
// `add(...)` returns the sum of a list of functions.
//
#ifndef CSYNTH_ADD_H
#define CSYNTH_ADD_H

#include <assert.h>
#include <stdarg.h>

#include "../core/func.h"
#include "./const.h"

double add_eval(Gen **args, int count, __attribute__((unused)) double delta, __attribute__((unused)) void *context)
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
    va_list valist;
    va_start(valist, count);
    Func *func = func_create_va(NULL, add_eval, NULL, 0, NULL, count, valist);
    va_end(valist);
    return func;
}

#define add(...) (add_args((sizeof((Func *[]){__VA_ARGS__}) / sizeof(Func **)), __VA_ARGS__))
#define add_(_input, _diff) (add(_input, const_(_diff)))

Func *add_array(int count, Func **args)
{
    return func_create_array(NULL, add_eval, NULL, 0, NULL, count, args);
}

void test_add()
{
    assert(gen_eval(gen_create(add(const_(1), const_(1)), .1)) == 2.0);
    assert(gen_eval(gen_create(add(const_(1), const_(2), const_(3)), .1)) == 6.0);
    assert(gen_eval(gen_create(add(const_(1)), .1)) == 1.0);
}

#endif // CSYNTH_ADD_H
