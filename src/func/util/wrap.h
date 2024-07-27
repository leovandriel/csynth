#ifndef CSYNTH_WRAP_H
#define CSYNTH_WRAP_H

#include "../../core/func.h"
#include "../../core/gen.h"

typedef double (*wrap_callback)(double input, void *context);

/** @see wrap_create */
typedef struct
{
    /** @brief Evaluation callback, invoked by the generator. */
    wrap_callback callback;
    /** @brief Callback context. */
    void *context;
} WrapContext;

static double wrap_eval(__U size_t count, Gen **args, Eval *eval, void *context_)
{
    WrapContext *context = (WrapContext *)context_;
    double input = gen_eval(args[0], eval);
    return context->callback(input, context->context);
}

/**
 * @brief Create a function that wraps a C function.
 *
 * This is a simplified version of `func_create` that only takes a single input.
 *
 * @param callback The callback function that maps the input sample to output.
 * @param input Input signal.
 * @param context Callback context.
 * @return Func* Wrap function.
 */
Func *wrap_create(wrap_callback callback, Func *input, void *context)
{
    WrapContext initial = {
        .callback = callback,
        .context = context,
    };
    return func_create(NULL, wrap_eval, NULL, sizeof(WrapContext), &initial, FuncFlagNone, input);
}

#endif // CSYNTH_WRAP_H
