//
// print.h - Prints a string once.
//
// `print(text, input)` prints a string the first time input is non-zero
//
#ifndef CSYNTH_PRINT_H
#define CSYNTH_PRINT_H

#include <stdio.h>

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../util/error.h"

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

static void print_free(__attribute__((unused)) int count, void *context_)
{
    PrintContext *context = (PrintContext *)context_;
    free_((char *)context->text);
}

Func *print(const char *text, Func *input)
{
    size_t size = strlen(text) + 1;
    char *copy = malloc_(size);
    if (copy == NULL)
    {
        return error_null(csErrorMemoryAlloc);
    }
    strncpy(copy, text, size);
    PrintContext initial = (PrintContext){
        .text = copy,
    };
    return func_create(NULL, print_eval, print_free, sizeof(PrintContext), &initial, FUNC_FLAG_DEFAULT, 1, input);
}

#endif // CSYNTH_PRINT_H
