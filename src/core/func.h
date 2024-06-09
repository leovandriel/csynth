//
// func.h - An interface for defining functions.
//
#ifndef CSYNTH_FUNC_H
#define CSYNTH_FUNC_H

#include <float.h>
#include <stdarg.h>
#include <string.h>

#include "../mem/alloc.h"
#include "./def.h"

static const double EPSILON = DBL_EPSILON * 2;

Func *func_list = NULL;

Func *func_create_int(init_callback init, eval_callback eval, free_callback free, size_t size, void *context, unsigned int flags, int count)
{
    void *initial = size > 0 && context != NULL ? calloc_(1, size) : NULL;
    if (initial != NULL && context != NULL)
    {
        memcpy(initial, context, size);
    }
    Func **args = count > 0 ? (Func **)calloc_(count, sizeof(Func *)) : NULL;
    Func *func = (Func *)calloc_(1, sizeof(Func));
    *func = (Func){
        .args = args,
        .count = count,
        .size = size,
        .initial = initial,
        .init = init,
        .eval = eval,
        .free = free,
        .flags = flags,
        .next = func_list,
    };
    func_list = func;
    return func;
}

Func *func_create_array(init_callback init, eval_callback eval, free_callback free, size_t size, void *context, unsigned int flags, int count, Func **args)
{
    Func *func = func_create_int(init, eval, free, size, context, flags, count);
    if (func->args)
    {
        memcpy(func->args, args, count * sizeof(Func *));
    }
    return func;
}

Func *func_create_va(init_callback init, eval_callback eval, free_callback free, size_t size, void *context, unsigned int flags, int count, va_list valist)
{
    Func *func = func_create_int(init, eval, free, size, context, flags, count);
    for (int i = 0; i < count; i++)
    {
        func->args[i] = va_arg(valist, Func *);
    }
    return func;
}

/**
 * Create a function with a variable number of arguments.
 *
 * This is at the core of the function system. A function represents a
 * mathematical operation that is evaluated for each audio sample. The function
 * can have any number of inputs, and can be used to create complex audio
 * effects.
 *
 * The function is defined by three callbacks:
 * - init: Called once before the first evaluation. This allows for things like
 *   memory allocation. Typical use cases are functions that keep an internal
 *   buffer like reverb or that open a file like wav.
 * - eval: Returns the value of the function, given inputs and time delta. This
 *   argument is required for all functions. There are no restrictions on the
 *   domain, though for audio functions it is typically in the range [-1, 1].
 * - free: Called once after the last evaluation. This allows for various
 *   cleanup tasks, like deallocating buffers or closing files.
 *
 * Additionally, the function can have a context struct, which is used to store
 * state between evaluations. This is useful for functions that need to keep
 * track of previous values, like a delay line or a filter.
 *
 * The function can have flags that control the behavior of the function. The
 * flags are defined in `def.h` and can be combined with the bitwise OR
 * operator. The default flags are `FUNC_FLAG_DEFAULT`.
 *
 * The function can have any number of inputs. The inputs are passed as a
 * variable number of arguments, and must be of type `Func *`.
 *
 * The return value is a pointer to the function, which can be used as an input
 * to other functions or as an output to the audio system.
 *
 * @param init Called once before the first evaluation.
 * @param eval Returns the value of the function, given inputs and time delta.
 * @param free Called once after the last evaluation.
 * @param size The size of the context struct.
 * @param context The initial value of the context.
 * @param flags Flags that control the behavior of the function.
 * @param count The number of inputs.
 * @param ... The inputs to the function.
 * @return The function output.
 */
Func *func_create(init_callback init, eval_callback eval, free_callback free, size_t size, void *context, unsigned int flags, int count, ...)
{
    va_list valist = {0};
    va_start(valist, count);
    Func *func = func_create_va(init, eval, free, size, context, flags, count, valist);
    va_end(valist);
    return func;
}

void func_free()
{
    while (func_list != NULL)
    {
        Func *func = func_list;
        func_list = func->next;
        if (func->args != NULL)
        {
            free_(func->args);
        }
        if (func->initial != NULL)
        {
            free_(func->initial);
        }
        free_(func);
    }
}

#endif // CSYNTH_FUNC_H
