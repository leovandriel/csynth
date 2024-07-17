//
// wrap.h - Func that is defined by a C function.
//
// `wrap(input, function)`
//
#ifndef CSYNTH_WRAP_H
#define CSYNTH_WRAP_H

#include "../../core/func.h"
#include "../../core/gen.h"

typedef double (*wrap_callback)(double input, void *context);

typedef struct
{
    wrap_callback callback;
    void *context;
} WrapFilterContext;

static double wrap_eval(__U size_t count, Gen **args, Eval *eval, void *context_)
{
    WrapFilterContext *context = (WrapFilterContext *)context_;
    double input = gen_eval(args[0], eval);
    return context->callback(input, context->context);
}

Func *wrap_create(wrap_callback callback, Func *input, void *context)
{
    WrapFilterContext initial = {
        .callback = callback,
        .context = context,
    };
    return func_create(NULL, wrap_eval, NULL, sizeof(WrapFilterContext), &initial, FuncFlagNone, input);
}

#endif // CSYNTH_WRAP_H
