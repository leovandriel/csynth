//
// square.h - A square function
//
// `square(frequency)` returns a square wave with the given frequency.
//
#ifndef CSYNTH_SQUARE_H
#define CSYNTH_SQUARE_H

#include <assert.h>
#include <math.h>

#include "../../core/func.h"
#include "../gen/const.h"

typedef struct
{
    double time;
    double output;
} SquareContext;

static double square_eval(Gen **args, __attribute__((unused)) int count, double delta, void *context_)
{
    SquareContext *context = (SquareContext *)context_;
    double span = 1.0 / (gen_eval(args[0]) * 2.0);
    if (context->time >= span)
    {
        context->time -= span;
        context->output = -context->output;
    }
    context->time += delta;
    return context->output;
}

Func *square(Func *frequency)
{
    SquareContext initial = (SquareContext){
        .output = 1.0,
    };
    return func_create(NULL, square_eval, NULL, sizeof(SquareContext), &initial, 1, frequency);
}

Func *square_(double frequency) { return square(const_(frequency)); }

void test_square()
{
    Func *t = square(const_(1));
    Gen *g = gen_create(t, 0.1);
    double epsilon = 1e-9;
    assert(fabs(gen_eval(g) - 1.0) < epsilon);
    assert(fabs(gen_eval(g) - 1.0) < epsilon);
    assert(fabs(gen_eval(g) - 1.0) < epsilon);
    assert(fabs(gen_eval(g) - 1.0) < epsilon);
    assert(fabs(gen_eval(g) - 1.0) < epsilon);
    assert(fabs(gen_eval(g) - -1.0) < epsilon);
    assert(fabs(gen_eval(g) - -1.0) < epsilon);
    assert(fabs(gen_eval(g) - -1.0) < epsilon);
    assert(fabs(gen_eval(g) - -1.0) < epsilon);
    assert(fabs(gen_eval(g) - -1.0) < epsilon);
    assert(fabs(gen_eval(g) - 1.0) < epsilon);
    assert(fabs(gen_eval(g) - 1.0) < epsilon);
}

#endif // CSYNTH_SQUARE_H
