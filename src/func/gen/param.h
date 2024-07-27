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
    return eval->params[context->param];
}

/**
 * @brief Create a function that returns the value of an eval parameter.
 *
 * Eval parameters allow for dynamic control of the synthesis process by passing
 * variables down the synthesis tree.
 *
 * @param param Eval parameter to return.
 * @return Func* Param function.
 */
Func *param_create(EvalParam param)
{
    ParamContext initial = {.param = param};
    return func_create(NULL, param_eval, NULL, sizeof(ParamContext), &initial, FuncFlagNone, );
}

/** @brief Shorthand for `param_create`. */
Func *param(EvalParam param) { return param_create(param); }

#endif // CSYNTH_PARAM_H
