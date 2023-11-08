//
// triangle.h - A triangle function
//
// `triangle(frequency)` returns a triangle wave with the given frequency.
//
#ifndef CSYNTH_TRIANGLE_H
#define CSYNTH_TRIANGLE_H

#include <assert.h>
#include <math.h>

#include "../../core/func.h"
#include "../gen/const.h"

typedef struct
{
    double last;
    double direction;
} TriangleContext;

static double triangle_eval(__attribute__((unused)) int count, Gen **args, double delta, void *context_)
{
    TriangleContext *context = (TriangleContext *)context_;
    double frequency = gen_eval(args[0]);
    double output = context->last;
    context->last += context->direction * frequency * delta;
    if (context->last > 1.0)
    {
        context->last = 2.0 - context->last;
        context->direction = -context->direction;
    }
    else if (context->last < -1.0)
    {
        context->last = -2.0 - context->last;
        context->direction = -context->direction;
    }
    return output;
}

Func *triangle(Func *frequency)
{
    TriangleContext initial = (TriangleContext){
        .direction = 4.0,
    };
    return func_create(NULL, triangle_eval, NULL, sizeof(TriangleContext), &initial, 1, frequency);
}

Func *triangle_(double frequency) { return triangle(const_(frequency)); }

void test_triangle()
{
    Func *t = triangle(const_(1));
    Gen *g = gen_create(t, 0.1);
    double epsilon = 1e-9;
    assert(fabs(gen_eval(g) - 0.0) < epsilon);
    assert(fabs(gen_eval(g) - 0.4) < epsilon);
    assert(fabs(gen_eval(g) - 0.8) < epsilon);
    assert(fabs(gen_eval(g) - 0.8) < epsilon);
    assert(fabs(gen_eval(g) - 0.4) < epsilon);
    assert(fabs(gen_eval(g) - -0.0) < epsilon);
    assert(fabs(gen_eval(g) - -0.4) < epsilon);
    assert(fabs(gen_eval(g) - -0.8) < epsilon);
    assert(fabs(gen_eval(g) - -0.8) < epsilon);
    assert(fabs(gen_eval(g) - -0.4) < epsilon);
    assert(fabs(gen_eval(g) - 0.0) < epsilon);
    assert(fabs(gen_eval(g) - 0.4) < epsilon);
}

#endif // CSYNTH_TRIANGLE_H
