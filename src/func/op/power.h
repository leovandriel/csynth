//
// power.h - Power function
//
// `power(a, b)` returns a ** b.
//
#ifndef CSYNTH_POWER_H
#define CSYNTH_POWER_H

#include "../../util/test.h"
#include "../../util/math.h"
#include "../../core/func.h"
#include "../gen/const.h"

static double power_eval(__attribute__((unused)) int count, Gen **args, __attribute__((unused)) double delta, __attribute__((unused)) void *context)
{
    double a = gen_eval(args[0]);
    double b = gen_eval(args[1]);
    return pow(a, b);
}

Func *power(Func *a, Func *b)
{
    return func_create(NULL, power_eval, NULL, 0, NULL, 2, a, b);
}

Func *power_(Func *input, double exponent) { return power(input, const_(exponent)); }

void test_power()
{
    assert_gen_equal(gen_create(power(const_(1), const_(1)), .1), 1.0);
    assert_gen_equal(gen_create(power(const_(1), const_(2)), .1), 1.0);
    assert_gen_equal(gen_create(power(const_(2), const_(1)), .1), 2.0);
    assert_gen_equal(gen_create(power(const_(2), const_(2)), .1), 4.0);
}

#endif // CSYNTH_POWER_H
