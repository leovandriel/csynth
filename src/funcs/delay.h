//
// delay.h - A time delay on the sampling of a function
//
// `delay(input, duration)` waits duration (a function) seconds before it starts
// sampling the input function.
//
#ifndef CSYNTH_DELAY_H
#define CSYNTH_DELAY_H

#include <assert.h>
#include <math.h>

#include "../core/func.h"
#include "./const.h"

typedef struct
{
    double time;
} DelayContext;

double delay_eval(Gen **args, __attribute__((unused)) int count, double delta, void *_context)
{
    DelayContext *context = (DelayContext *)_context;
    double span = gen_eval(args[1]);
    double output = 0.0;
    while (context->time >= span)
    {
        output = gen_eval(args[0]);
        context->time -= delta;
    }
    context->time += delta;
    return output;
}

Func *delay(Func *input, Func *duration)
{
    return func_create(NULL, delay_eval, NULL, sizeof(DelayContext), NULL, 2, input, duration);
}

#define delay_(_input, _frequency) (delay(_input, const_(_frequency)))
#define skip(_input, _duration) (delay(_input, neg(_duration)))
#define skip_(_input, _duration) (skip(_input, const_(_duration)))

void test_delay()
{
    func t = delay(const_(1), const_(0.5));
    Gen *g = gen_create(t, 0.1);
    double epsilon = 1e-9;
    assert(fabs(gen_eval(g) - 0.000000) < epsilon);
    assert(fabs(gen_eval(g) - 0.000000) < epsilon);
    assert(fabs(gen_eval(g) - 0.000000) < epsilon);
    assert(fabs(gen_eval(g) - 0.000000) < epsilon);
    assert(fabs(gen_eval(g) - 0.000000) < epsilon);
    assert(fabs(gen_eval(g) - 1.000000) < epsilon);
    assert(fabs(gen_eval(g) - 1.000000) < epsilon);
    assert(fabs(gen_eval(g) - 1.000000) < epsilon);
    assert(fabs(gen_eval(g) - 1.000000) < epsilon);
    assert(fabs(gen_eval(g) - 1.000000) < epsilon);
    assert(fabs(gen_eval(g) - 1.000000) < epsilon);
    assert(fabs(gen_eval(g) - 1.000000) < epsilon);
    assert(fabs(gen_eval(g) - 1.000000) < epsilon);
    assert(fabs(gen_eval(g) - 1.000000) < epsilon);
}

#endif // CSYNTH_DELAY_H
