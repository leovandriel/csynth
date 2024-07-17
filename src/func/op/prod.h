//
// prod.h - Multiply input values over time.
//
#ifndef CSYNTH_PROD_H
#define CSYNTH_PROD_H

#include "../../core/func.h"
#include "../../core/gen.h"

typedef struct
{
    double prod;
} ProdContext;

static double prod_eval(__U size_t count, Gen **args, Eval *eval, void *context_)
{
    ProdContext *context = (ProdContext *)context_;
    double output = context->prod;
    context->prod *= gen_eval(args[0], eval);
    return output;
}

Func *prod_create(Func *input)
{
    ProdContext initial = {.prod = 1.0};
    return func_create(NULL, prod_eval, NULL, sizeof(ProdContext), &initial, FuncFlagNone, input);
}

#endif // CSYNTH_PROD_H
