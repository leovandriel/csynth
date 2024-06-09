//
// wrap.h - Func that is defined by a C function.
//
// `wrap(input, function, context)`
//
#ifndef CSYNTH_WRAP_H
#define CSYNTH_WRAP_H

#include "../../core/func.h"
#include "../../core/gen.h"

typedef double (*wrap_filter_callback)(double input, double delta, void *context);

typedef struct
{
    wrap_filter_callback callback;
    void *context;
} WrapFilterContext;

static double wrap_filter_eval(__attribute__((unused)) int count, Gen **args, __attribute__((unused)) double delta, void *context_)
{
    WrapFilterContext *context = (WrapFilterContext *)context_;
    return context->callback(gen_eval(args[0]), delta, context->context);
}

Func *wrap_filter(Func *input, wrap_filter_callback callback, void *context)
{
    WrapFilterContext initial = (WrapFilterContext){
        .callback = callback,
        .context = context,
    };
    return func_create(NULL, wrap_filter_eval, NULL, sizeof(WrapFilterContext), &initial, FUNC_FLAG_DEFAULT, 1, input);
}

typedef double (*wrap_gen_callback)(double time, void *context);

typedef struct
{
    wrap_gen_callback callback;
    double time;
    void *context;
} WrapGenContext;

static double wrap_gen_eval(__attribute__((unused)) int count, __attribute__((unused)) Gen **args, __attribute__((unused)) double delta, void *context_)
{
    WrapGenContext *context = (WrapGenContext *)context_;
    double output = context->callback(context->time, context->context);
    context->time += delta;
    return output;
}

Func *wrap_gen(wrap_gen_callback callback, void *context)
{
    WrapGenContext initial = (WrapGenContext){
        .callback = callback,
        .context = context,
    };
    return func_create(NULL, wrap_gen_eval, NULL, sizeof(WrapGenContext), &initial, FUNC_FLAG_DEFAULT, 0);
}

#endif // CSYNTH_WRAP_H
