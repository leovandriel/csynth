//
// crack.h - A crackling function
//
#ifndef CSYNTH_CRACK_H
#define CSYNTH_CRACK_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../util/rand.h"
#include "./const.h"

static double crack_eval(__attribute__((unused)) int count, Gen **args, __attribute__((unused)) double delta, __attribute__((unused)) void *context_)
{
    double probability = gen_eval(args[0]);
    return rand_range(0, 1) < probability ? rand_range(-1, 1) : 0;
}

Func *crack(Func *probability)
{
    return func_create(NULL, crack_eval, NULL, 0, NULL, FUNC_FLAG_DEFAULT, 1, probability);
}

Func *crack_(double probability) { return crack(const_(probability)); }

#endif // CSYNTH_CRACK_H
