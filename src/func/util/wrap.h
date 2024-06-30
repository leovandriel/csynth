//
// wrap.h - Func that is defined by a C function.
//
// `wrap(input, function)`
//
#ifndef CSYNTH_WRAP_H
#define CSYNTH_WRAP_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../func/time/times.h"

typedef double (*wrap_callback)(double input);

typedef struct
{
    wrap_callback callback;
} WrapFilterContext;

static double wrap_eval(__U int count, Gen **args, Eval eval, void *context_)
{
    WrapFilterContext *context = (WrapFilterContext *)context_;
    return context->callback(gen_eval(args[0], eval));
}

Func *wrap(wrap_callback callback, Func *input)
{
    WrapFilterContext initial = {.callback = callback};
    return func_create(NULL, wrap_eval, NULL, sizeof(WrapFilterContext), &initial, FuncFlagNone, FUNCS(input));
}

Func *wrap_(wrap_callback callback) { return wrap(callback, pitch_timer_(1)); }

#endif // CSYNTH_WRAP_H
