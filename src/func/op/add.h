#ifndef CSYNTH_ADD_H
#define CSYNTH_ADD_H

#include "../../core/func.h"
#include "../../core/gen.h"

static double add_eval(size_t count, Gen **args, Eval *eval, __U void *context)
{
    double sum = 0;
    for (size_t i = 0; i < count; i++)
    {
        sum += gen_eval(args[i], eval);
    }
    return sum;
}

/**
 * @brief Create a function that sums across all inputs.
 *
 * Can be used to mix multiple signals together.
 *
 * @param count Number of arguments.
 * @param args Argument array.
 * @return Func* Addition function.
 */
Func *add_create(size_t count, Func **args)
{
    return func_create_args(NULL, add_eval, NULL, 0, NULL, FuncFlagNone, count, args, "arg");
}

#endif // CSYNTH_ADD_H
