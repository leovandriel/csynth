//
// tanh.h - tanh function
//
#ifndef CSYNTH_TANH_H
#define CSYNTH_TANH_H

#include <math.h>

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../gen/const.h"

static double tanh_eval(__attribute__((unused)) int count, Gen **args, __attribute__((unused)) double delta, __attribute__((unused)) void *context)
{
    double x = gen_eval(args[0]);
    return tanh(x);
}

Func *tanh_op(Func *f)
{
    return func_create(NULL, tanh_eval, NULL, 0, NULL, FUNC_FLAG_DEFAULT, 1, f);
}

#endif // CSYNTH_TANH_H
