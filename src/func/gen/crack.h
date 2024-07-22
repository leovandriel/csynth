//
// crack.h - A crackling function
//
#ifndef CSYNTH_CRACK_H
#define CSYNTH_CRACK_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../util/rand.h"

typedef struct
{
    Random random;
} CrackContext;

static double crack_eval(__U size_t count, Gen **args, Eval *eval, __U void *context_)
{
    CrackContext *context = (CrackContext *)context_;
    double tick = gen_eval(args[0], eval);
    return random_range(&context->random, 0, 1) < tick ? random_range(&context->random, -1, 1) : 0;
}

Func *crack_create(Func *tick)
{
    CrackContext initial = {.random = random_create(0)};
    return func_create(NULL, crack_eval, NULL, sizeof(CrackContext), &initial, FuncFlagNone, tick);
}

#endif // CSYNTH_CRACK_H
