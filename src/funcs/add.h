//
// add.h - Addition function
//
// `add(...)` returns the sum of a list of functions.
//
#ifndef COMPOSER_ADD_H
#define COMPOSER_ADD_H

#include <assert.h>
#include <stdarg.h>

#include "../core/func.h"
#include "./cons.h"

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

#define add(...) add_args((sizeof((Func *[]){__VA_ARGS__}) / sizeof(Func **)), __VA_ARGS__)

void test_add()
{
    assert(gen_eval(gen_create(add(cons(1), cons(1)), .1)) == 2.0);
    assert(gen_eval(gen_create(add(cons(1), cons(2), cons(3)), .1)) == 6.0);
    assert(gen_eval(gen_create(add(cons(1)), .1)) == 1.0);
}

#endif // COMPOSER_ADD_H
