#ifndef CSYNTH_TRIANGLE_H
#define CSYNTH_TRIANGLE_H

#include "../../core/func.h"
#include "../../core/gen.h"

/** @see triange_create */
typedef struct
{
    /** @brief Previous output value. */
    double last;
    /** @brief Direction of the triangle wave. */
    double direction;
} TriangleContext;

static double triangle_eval(__U size_t count, Gen **args, Eval *eval, void *context_)
{
    TriangleContext *context = (TriangleContext *)context_;
    double output = context->last;
    double tick = gen_eval(args[0], eval);
    context->last += context->direction * tick;
    if (context->last > 1.0)
    {
        context->last = 2.0 - context->last;
        context->direction = -context->direction;
    }
    else if (context->last < -1.0)
    {
        context->last = -2.0 - context->last;
        context->direction = -context->direction;
    }
    return output;
}

/**
 * @brief Create a function that outputs a triangle wave.
 *
 * @param tick Periods per sample.
 * @return Func* Triangle function.
 */
Func *triangle_create(Func *tick)
{
    TriangleContext initial = {.direction = 4.0};
    return func_create(NULL, triangle_eval, NULL, sizeof(TriangleContext), &initial, FuncFlagNone, tick);
}

#endif // CSYNTH_TRIANGLE_H
