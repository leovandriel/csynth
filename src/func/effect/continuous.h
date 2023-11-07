//
// continuous.h - Prevents its input from being reset
//
// `continuous(input)` 
//
#ifndef CSYNTH_CONTINUOUS_H
#define CSYNTH_CONTINUOUS_H

#include <assert.h>

#include "../../core/func.h"

Func *continuous(Func *input)
{
    return func_create(NULL, continuous_eval, NULL, 0, NULL, 1, input);
}

void test_continuous()
{
}

#endif // CSYNTH_CONTINUOUS_H
