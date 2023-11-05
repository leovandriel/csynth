#ifndef COMPOSER_NOISE_H
#define COMPOSER_NOISE_H

#include <stdlib.h>

#include "../core/func.h"

double noise_eval(__attribute__((unused)) Gen **args, __attribute__((unused)) int count, __attribute__((unused)) double delta, __attribute__((unused)) void *context)
{
    return 2.0 * rand() / RAND_MAX - 1.0;
}

Func *noise()
{
    return func_create(NULL, noise_eval, NULL, 0, NULL, 0);
}

#endif // COMPOSER_NOISE_H
