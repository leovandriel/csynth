//
// wrap.h - Func that is defined by a C function.
//
// `wrap(input, function)`
//
#ifndef CSYNTH_WRAP_H
#define CSYNTH_WRAP_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../func/gen/timer.h"

typedef double (*wrap_callback)(double input, double delta);

typedef struct
{
    wrap_callback callback;
} WrapFilterContext;

static double wrap_eval(__attribute__((unused)) int count, Gen **args, __attribute__((unused)) double delta, void *context_)
{
    WrapFilterContext *context = (WrapFilterContext *)context_;
    return context->callback(gen_eval(args[0]), delta);
}

Func *wrap(Func *input, wrap_callback callback)
{
    WrapFilterContext initial = (WrapFilterContext){
        .callback = callback,
    };
    return func_create(NULL, wrap_eval, NULL, sizeof(WrapFilterContext), &initial, FUNC_FLAG_DEFAULT, 1, input);
}

Func *wrap_(wrap_callback callback) { return wrap(timer(), callback); }

#endif // CSYNTH_WRAP_H
