#ifndef CSYNTH_PROD_H
#define CSYNTH_PROD_H

#include "../../core/func.h"
#include "../../core/gen.h"

/** @see prod_create */
typedef struct
{
    /** @brief Accumulated product. */
    double prod;
} ProdContext;

static double prod_eval(__U size_t count, Gen **args, Eval *eval, void *context_)
{
    ProdContext *context = (ProdContext *)context_;
    double output = context->prod;
    context->prod *= gen_eval(args[0], eval);
    return output;
}

/**
 * @brief Create a function that accumulates the product over time, across
 * samples.
 *
 * @param input Input function.
 * @return Func* Product function.
 */
Func *prod_create(Func *input)
{
    ProdContext initial = {.prod = 1.0};
    return func_create(NULL, prod_eval, NULL, sizeof(ProdContext), &initial, FuncFlagNone, input);
}

#endif // CSYNTH_PROD_H
