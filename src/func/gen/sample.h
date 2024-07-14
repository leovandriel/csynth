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
    double sample;
} SampleContext;

static double sample_eval(__U size_t count, __U Gen **args, __U Eval *eval, void *context_)
{
    SampleContext *context = (SampleContext *)context_;
    if (context->sample == 0.0)
    {
        context->sample = rand_uniform();
    }
    return context->sample;
}

Func *sample_create()
{
    return func_create(NULL, sample_eval, NULL, sizeof(SampleContext), NULL, FuncFlagNone, ARGS());
}

#endif // CSYNTH_SAMPLE_H
