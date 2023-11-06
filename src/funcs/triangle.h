//
// triangle.h - A triangle function
//
// `triangle(frequency)` returns a triangle wave with the given frequency.
//
#ifndef COMPOSER_TRIANGLE_H
#define COMPOSER_TRIANGLE_H

#include <assert.h>
#include <math.h>

#include "../core/func.h"
#include "./cons.h"

typedef struct
{
    double last;
    double direction;
} TriangleContext;

double triangle_eval(Gen **args, __attribute__((unused)) int count, double delta, void *_context)
{
    TriangleContext *context = (TriangleContext *)_context;
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

void test_triangle()
{
    func t = triangle(cons(1));
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

#endif // COMPOSER_TRIANGLE_H
