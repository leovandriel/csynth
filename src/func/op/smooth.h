#ifndef CSYNTH_SMOOTH_H
#define CSYNTH_SMOOTH_H

#include "../../core/func.h"
#include "../../core/gen.h"

static double smooth_eval(__U size_t count, Gen **args, Eval *eval, __U void *context_)
{
    double edge0 = gen_eval(args[0], eval);
    double edge1 = gen_eval(args[1], eval);
    double input = gen_eval(args[2], eval);
    if ((edge0 <= edge1 && input < edge0) || (edge0 > edge1 && input >= edge0))
    {
        return 0.0;
    }
    if ((edge0 >= edge1 && input <= edge1) || (edge0 <= edge1 && input >= edge1))
    {
        return 1.0;
    }
    double ratio = (input - edge0) / (edge1 - edge0);
    return ratio * ratio * (3.0 - 2.0 * ratio);
}

/**
 * @brief Create a function for the smooth step function, i.e. 0 if input <
 * edge0, 1 if input > edge1, otherwise smooth interpolation.
 *
 * If first > second, the function is reversed, i.e. 1 - smooth()
 *
 * @param edge0 First edge.
 * @param edge1 Second edge.
 * @param input Input value.
 * @return Func* Smooth function.
 */
Func *smooth_create(Func *edge0, Func *edge1, Func *input)
{
    return func_create(NULL, smooth_eval, NULL, 0, NULL, FuncFlagNone, edge0, edge1, input);
}

#endif // CSYNTH_SMOOTH_H
