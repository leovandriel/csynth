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

#include <assert.h>
#include <math.h>

#include "../core/func.h"
#include "./cons.h"

typedef struct
{
    double time;
} SmoothContext;

double smooth_eval(Gen **args, __attribute__((unused)) int count, double delta, void *_context)
{
    SmoothContext *context = (SmoothContext *)_context;
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

#define smooth_(_edge0, _edge1) ((cons(_edge0), cons(_edge1)))
#define hump(_edge0, _edge1, _edge2, _edge3) (mul(smooth(_edge0, _edge1), add(ONE, neg(smooth(_edge2, _edge3)))))
#define hump_(_edge0, _edge1, _edge2, _edge3) (hump(cons(_edge0), cons(_edge1), cons(_edge2), cons(_edge3)))

void test_smooth()
{
    func t = smooth(cons(0.3), cons(0.7));
    Gen *g = gen_create(t, 0.1);
    double epsilon = 1e-4;
    assert(fabs(gen_eval(g) - 0.000000) < epsilon);
    assert(fabs(gen_eval(g) - 0.000000) < epsilon);
    assert(fabs(gen_eval(g) - 0.000000) < epsilon);
    assert(fabs(gen_eval(g) - 0.000000) < epsilon);
    assert(fabs(gen_eval(g) - 0.156250) < epsilon);
    assert(fabs(gen_eval(g) - 0.500000) < epsilon);
    assert(fabs(gen_eval(g) - 0.843750) < epsilon);
    assert(fabs(gen_eval(g) - 1.000000) < epsilon);
    assert(fabs(gen_eval(g) - 1.000000) < epsilon);
    assert(fabs(gen_eval(g) - 1.000000) < epsilon);
}

#endif // CSYNTH_SMOOTH_H
