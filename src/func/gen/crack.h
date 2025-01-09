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
 * This function creates a generator that produces random "crackle" sounds by
 * outputting random values at random intervals. Each sample has a probability
 * (controlled by tick) of being a random value in [-1, 1], otherwise it outputs 0.
 *
 * The crackle effect is useful for:
 * - Simulating vinyl record noise/pops
 * - Creating fire/static sound effects
 * - Adding gritty texture to sounds
 * - Generating sparse random impulses
 *
 * The random values and timing use a dedicated random number generator initialized
 * with seed 0, so the pattern will be consistent between runs but independent of
 * other random generators.
 *
 * @param tick Function controlling probability of crackle. Should output values in
 *            range [0, 1]. Higher values create more frequent crackles:
 *            - 0.0: Silent (no crackles)
 *            - 0.1: Sparse occasional crackles
 *            - 0.5: Moderate density
 *            - 1.0: Maximum density (random noise)
 * @return Func* Crackle function that outputs random values or zero based on probability.
 */
Func *crack_create(Func *tick)
{
    CrackContext initial = {.random = random_create(0)};
    return func_create(NULL, crack_eval, NULL, NULL, sizeof(CrackContext), &initial, FuncFlagNone, tick);
}

#endif // CSYNTH_CRACK_H
