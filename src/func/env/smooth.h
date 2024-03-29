//
// smooth.h - A smooth step function
//
// `smooth(edge0, edge1)` returns 1 if time is past edge1, 0 before edge0.
// - hump(edge0, edge1, edge2, edge3) - A smooth block function, which is 1
//   between edge1 and edge2 and 0 before edge0 and after edge3
// - hump_ - Take double arguments instead of functions
//
#ifndef CSYNTH_SMOOTH_H
#define CSYNTH_SMOOTH_H

#include "../../util/test.h"
#include "../../core/func.h"
#include "../gen/const.h"

typedef struct
{
    double time;
} SmoothContext;

static double smooth_eval(__attribute__((unused)) int count, Gen **args, double delta, void *context_)
{
    SmoothContext *context = (SmoothContext *)context_;
    double edge0 = gen_eval(args[0]);
    double edge1 = gen_eval(args[1]);
    if (context->time <= edge0)
    {
        context->time += delta;
        return 0.0;
    }
    else if (context->time >= edge1)
    {
        context->time += delta;
        return 1.0;
    }
    else
    {
        double s = (context->time - edge0) / (edge1 - edge0);
        context->time += delta;
        return s * s * (3.0 - 2.0 * s);
    }
}

Func *smooth(Func *edge0, Func *edge1)
{
    return func_create(NULL, smooth_eval, NULL, sizeof(SmoothContext), NULL, 2, edge0, edge1);
}

Func *smooth_(double edge0, double edge1) { return smooth(const_(edge0), const_(edge1)); }

void test_smooth()
{
    Func *t = smooth(const_(0.3), const_(0.7));
    Gen *g = gen_create(t, 0.1);
    assert_gen_equal(g, 0.000000);
    assert_gen_equal(g, 0.000000);
    assert_gen_equal(g, 0.000000);
    assert_gen_equal(g, 0.000000);
    assert_gen_equal(g, 0.156250);
    assert_gen_equal(g, 0.500000);
    assert_gen_equal(g, 0.843750);
    assert_gen_equal(g, 1.000000);
    assert_gen_equal(g, 1.000000);
    assert_gen_equal(g, 1.000000);
}

#endif // CSYNTH_SMOOTH_H
