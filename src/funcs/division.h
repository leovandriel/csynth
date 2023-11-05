//
// division.h - Division function
//
// `division(a, b)` returns a / b.
//
#ifndef COMPOSER_DIVISION_H
#define COMPOSER_DIVISION_H

#include "../core/func.h"

static const double DIVISION_EPSILON = 1e-9;

double division_eval(Gen **args, __attribute__((unused)) int count, __attribute__((unused)) double delta, __attribute__((unused)) void *context)
{
    double a = gen_eval(args[0]);
    double b = gen_eval(args[1]);
    return a / (fabs(b) > DIVISION_EPSILON ? b : DIVISION_EPSILON);
}

Func *division(Func *a, Func *b)
{
    return func_create(NULL, division_eval, NULL, 0, NULL, 2, a, b);
}

#endif // COMPOSER_DIVISION_H
