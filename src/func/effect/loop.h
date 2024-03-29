//
// loop.h - A time loop on the sampling of a function
//
// `loop(input, duration)` loops the input function every duration (a function).
//
#ifndef CSYNTH_LOOP_H
#define CSYNTH_LOOP_H

#include "../../util/test.h"
#include "../../core/func.h"
#include "../gen/const.h"
#include "../env/step.h"

typedef struct
{
    double time;
} LoopContext;

static double loop_eval(__attribute__((unused)) int count, Gen **args, double delta, void *context_)
{
    LoopContext *context = (LoopContext *)context_;
    double duration = gen_eval(args[1]);
    if (context->time >= duration)
    {
        context->time -= duration;
        gen_reset(args[0]);
    }
    double output = gen_eval(args[0]);
    context->time += delta;
    return output;
}

Func *loop(Func *input, Func *duration)
{
    return func_create(NULL, loop_eval, NULL, sizeof(LoopContext), NULL, 2, input, duration);
}

Func *loop_(Func *input, double duration) { return loop(input, const_(duration)); }

void test_loop()
{
    Func *t = loop(step(const_(0.3)), const_(0.5));
    Gen *g = gen_create(t, 0.1);
    assert_gen_equal(g, 0.0);
    assert_gen_equal(g, 0.0);
    assert_gen_equal(g, 0.0);
    assert_gen_equal(g, 1.0);
    assert_gen_equal(g, 1.0);
    assert_gen_equal(g, 0.0);
    assert_gen_equal(g, 0.0);
    assert_gen_equal(g, 0.0);
    assert_gen_equal(g, 1.0);
    assert_gen_equal(g, 1.0);
    assert_gen_equal(g, 0.0);
    assert_gen_equal(g, 0.0);
}

#endif // CSYNTH_LOOP_H
