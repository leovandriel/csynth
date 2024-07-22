//
// sample.h - Uniform sample once
//
#ifndef CSYNTH_SAMPLE_H
#define CSYNTH_SAMPLE_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../util/rand.h"

typedef struct
{
    Random random;
    double sample;
} SampleContext;

static double sample_eval(__U size_t count, __U Gen **args, __U Eval *eval, void *context_)
{
    SampleContext *context = (SampleContext *)context_;
    if (context->sample == 0.0)
    {
        context->sample = random_uniform(&context->random);
    }
    return context->sample;
}

Func *sample_create(void)
{
    SampleContext initial = {.random = random_create(0)};
    return func_create(NULL, sample_eval, NULL, sizeof(SampleContext), &initial, FuncFlagNone, );
}

#endif // CSYNTH_SAMPLE_H
