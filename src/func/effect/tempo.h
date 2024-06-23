//
// tempo.h - Tempo shift
//
#ifndef CSYNTH_TEMP_H
#define CSYNTH_TEMP_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../gen/const.h"

static double tempo_eval(__U int count, Gen **args, Eval eval, __U void *context_)
{
    eval.control_step *= gen_eval(args[1], eval);
    return gen_eval(args[0], eval);
}

Func *tempo(Func *input, Func *factor)
{
    return func_create(NULL, tempo_eval, NULL, 0, NULL, FuncFlagNone, 2, input, factor);
}

Func *tempo_(Func *input, double factor) { return tempo(input, const_(factor)); }

#endif // CSYNTH_TEMP_H
