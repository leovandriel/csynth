//
// power.h - Power function
//
// `power(a, b)` returns a ** b.
//
#ifndef COMPOSER_POWER_H
#define COMPOSER_POWER_H

#include <assert.h>
#include <math.h>

#include "../core/func.h"
#include "./cons.h"

double power_eval(Gen **args, __attribute__((unused)) int count, __attribute__((unused)) double delta, __attribute__((unused)) void *context)
{
    double a = gen_eval(args[0]);
    double b = gen_eval(args[1]);
    return pow(a, b);
}

Func *power(Func *a, Func *b)
{
    return func_create(NULL, power_eval, NULL, 0, NULL, 2, a, b);
}

void test_power()
{
    assert(gen_eval(gen_create(power(cons(1), cons(1)), .1)) == 1.0);
    assert(gen_eval(gen_create(power(cons(1), cons(2)), .1)) == 1.0);
    assert(gen_eval(gen_create(power(cons(2), cons(1)), .1)) == 2.0);
    assert(gen_eval(gen_create(power(cons(2), cons(2)), .1)) == 4.0);
}

#endif // COMPOSER_POWER_H
