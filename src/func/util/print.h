//
// print.h - Prints a string once.
//
// `print(text, input)` prints a string the first time input is non-zero
//
#ifndef CSYNTH_PRINT_H
#define CSYNTH_PRINT_H

#include <stdio.h>

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

void print_free(void *context_)
{
    PrintContext *context = (PrintContext *)context_;
    free((char *)context->text);
}

Func *print(const char *text, Func *input)
{
    char *copy = malloc(strlen(text) + 1);
    strcpy(copy, text);
    PrintContext initial = (PrintContext){
        .text = copy,
    };
    return func_create(NULL, print_eval, NULL, sizeof(PrintContext), &initial, FUNC_FLAG_DEFAULT, 1, input);
}

#endif // CSYNTH_PRINT_H
