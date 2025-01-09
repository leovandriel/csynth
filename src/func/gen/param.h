#ifndef CSYNTH_PARAM_H
#define CSYNTH_PARAM_H

#include "../../core/func.h"
#include "../../core/gen.h"

/** @see param_create */
typedef struct
{
    /** @brief Eval parameter to return. */
    EvalParam param;
} ParamContext;

static double param_eval(__U size_t count, __U Gen **args, Eval *eval, void *context_)
{
    ParamContext *context = (ParamContext *)context_;
    return eval != NULL ? eval->params[context->param] : 0.0;
}

/**
 * @brief Create a function that returns the value of an eval parameter.
 *
 * Eval parameters allow for dynamic control of the synthesis process by passing
 * variables down the synthesis tree. Each Eval struct contains an array of
 * parameter values that can be accessed by functions during evaluation.
 *
 * When the created function is evaluated, it looks up and returns the value of
 * the specified parameter from the current Eval context. If no Eval context is
 * provided (eval is NULL), it returns 0.0 as a default value.
 *
 * This provides a way to modulate synthesis parameters like frequency,
 * amplitude, or filter cutoffs dynamically at runtime without modifying the
 * synthesis tree structure. The parameter values can be updated between
 * evaluation calls to create time-varying effects.
 *
 * @param param Index of the eval parameter to return. Must be a valid index
 *             into the Eval params array.
 * @return Func* Parameter accessor function that outputs the current value of
 *              the specified eval parameter.
 */
Func *param_create(EvalParam param)
{
    ParamContext initial = {.param = param};
    return func_create(NULL, param_eval, NULL, NULL, sizeof(ParamContext), &initial, FuncFlagNone);
}

/** @brief Shorthand for `param_create`. */
Func *param(EvalParam param) { return param_create(param); }

#endif // CSYNTH_PARAM_H
