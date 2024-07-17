//
// param.h - Turn eval parameter into function output
//
#ifndef CSYNTH_PARAM_H
#define CSYNTH_PARAM_H

#include "../../core/func.h"
#include "../../core/gen.h"

typedef struct
{
    EvalParam param;
} ParamContext;

static double param_eval(__U size_t count, __U Gen **args, Eval *eval, void *context_)
{
    ParamContext *context = (ParamContext *)context_;
    return eval->params[context->param];
}

Func *param_create(EvalParam param)
{
    ParamContext initial = {.param = param};
    return func_create(NULL, param_eval, NULL, sizeof(ParamContext), &initial, FuncFlagNone, );
}

Func *param(EvalParam param) { return param_create(param); }

#endif // CSYNTH_PARAM_H
