//
// print.h - Prints a string once.
//
// `print(text, input)` prints a string the first time input is non-zero
//
#ifndef CSYNTH_PRINT_H
#define CSYNTH_PRINT_H

#include <stdio.h>

#include "../../util/test.h"
#include "../../core/func.h"

typedef struct
{
    const char *text;
} PrintContext;

static double print_eval(__attribute__((unused)) int count, Gen **args, __attribute__((unused)) double delta, void *context_)
{
    PrintContext *context = (PrintContext *)context_;
    double output = gen_eval(args[0]);
    if ((output > EPSILON || output < -EPSILON) && context->text != NULL)
    {
        fprintf(stderr, "%s\n", context->text);
        context->text = NULL;
    }
    return output;
}

Func *print(const char *text, Func *input)
{
    PrintContext initial = (PrintContext){
        .text = text,
    };
    return func_create(NULL, print_eval, NULL, sizeof(PrintContext), &initial, 1, input);
}

void test_print()
{
}

#endif // CSYNTH_PRINT_H
