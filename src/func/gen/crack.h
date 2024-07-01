//
// crack.h - A crackling function
//
#ifndef CSYNTH_CRACK_H
#define CSYNTH_CRACK_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../util/rand.h"

static double crack_eval(__U int count, Gen **args, Eval eval, __U void *context_)
{
    double tick = gen_eval(args[0], eval);
    return rand_range(0, 1) < tick ? rand_range(-1, 1) : 0;
}

Func *crack_create(Func *tick)
{
    return func_create(NULL, crack_eval, NULL, 0, NULL, FuncFlagNone, FUNCS(tick));
}

#endif // CSYNTH_CRACK_H
