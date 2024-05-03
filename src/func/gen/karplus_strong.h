//
// karplus_strong.h - Karplus-Strong algorithm
//
// `karplus_strong(frequency, decay)`
//
#ifndef CSYNTH_KARPLUS_STRONG_H
#define CSYNTH_KARPLUS_STRONG_H

#include "../../util/math.h"
#include "../../util/test.h"
#include "../../core/func.h"
#include "../../util/buffer.h"
#include "./const.h"

typedef struct
{
    Buffer buffer;
    unsigned long index;
} KarplusStrongContext;

static double karplus_strong_eval(__attribute__((unused)) int count, Gen **args, double delta, void *context_)
{
    KarplusStrongContext *context = (KarplusStrongContext *)context_;
    double frequency = gen_eval(args[0]);
    unsigned long size = (unsigned long)(1.0 / (delta * frequency) + 0.5);
    double decay = pow(gen_eval(args[1]), 1.0 / size);
    context->index = buffer_resize(&context->buffer, size, context->index, fill_rand_1_1);
    unsigned long next = (context->index + 1) % size;
    double *buffer = context->buffer.samples;
    buffer[context->index] = 0.5 * (buffer[context->index] + buffer[next]) * decay;
    double output = buffer[context->index];
    context->index = next;
    return output;
}

void karplus_strong_free(void *context_)
{
    KarplusStrongContext *context = (KarplusStrongContext *)context_;
    buffer_free(&context->buffer);
}

Func *karplus_strong(Func *frequency, Func *decay)
{
    return func_create(NULL, karplus_strong_eval, karplus_strong_free, sizeof(KarplusStrongContext), NULL, 2, frequency, decay);
}

Func *karplus_strong_(double frequency, double decay) { return karplus_strong(const_(frequency), const_(decay)); }

void test_karplus_strong()
{
    rand_seed(0);
    Func *t = karplus_strong(const_(2), const_(0.5));
    Gen *g = gen_create(t, 0.1);
    assert_gen_equal(g, -0.2886412523525353);
    assert_gen_equal(g, 0.4912185886479782);
    assert_gen_equal(g, 0.4195619192984845);
    assert_gen_equal(g, 0.4241761877148519);
    assert_gen_equal(g, 0.2779732095631874);
    assert_gen_equal(g, 0.0881769071115131);
    assert_gen_equal(g, 0.3964402421159615);
    assert_gen_equal(g, 0.3672583421674327);
    assert_gen_equal(g, 0.3056282766592155);
    assert_gen_equal(g, 0.1593760951610511);
    assert_gen_equal(g, 0.2109418661214700);
    assert_gen_equal(g, 0.3324191163681807);
}

#endif // CSYNTH_KARPLUS_STRONG_H
