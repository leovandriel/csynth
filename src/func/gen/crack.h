#ifndef CSYNTH_CRACK_H
#define CSYNTH_CRACK_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../util/random.h"

/** @see crack_create */
typedef struct
{
    /** @brief Random number generator. */
    Random random;
} CrackContext;

static double crack_eval(__U size_t count, Gen **args, Eval *eval, __U void *context_)
{
    CrackContext *context = (CrackContext *)context_;
    double tick = gen_eval(args[0], eval);
    return random_uniform_range(&context->random, 0, 1) < tick ? random_uniform_range(&context->random, -1, 1) : 0;
}

/**
 * @brief Create a function that outputs a pseudo random value at pseudo random
 * intervals, and zero in between.
 *
 * @param tick In range [0, 1], the probability of a crackle.
 * @return Func* Crackle function.
 */
Func *crack_create(Func *tick)
{
    CrackContext initial = {.random = random_create(0)};
    return func_create(NULL, crack_eval, NULL, sizeof(CrackContext), &initial, FuncFlagNone, tick);
}

#endif // CSYNTH_CRACK_H
