//
// func.h - An interface for defining functions.
//
#ifndef CSYNTH_FUNC_H
#define CSYNTH_FUNC_H

#include <float.h>
#include <string.h>

#include "../mem/alloc.h"
#include "../util/error.h"
#include "./def.h"

#define ARRAY(__type, ...) ((__type[]){__VA_ARGS__})
#define ARRAY_SIZE(__array) (sizeof((__array)) / sizeof((__array)[0]))
#define ARRAY_ARGS(__array) ARRAY_SIZE(__array), (__array)
#define ARGS(...) ARRAY_ARGS(ARRAY(Func *, __VA_ARGS__))
#define ARGS_COUNT(...) ARRAY_SIZE(ARRAY(Func *, __VA_ARGS__))

static const double FUNC_EPSILON = DBL_EPSILON * 2;
static const double FUNC_AUDIBLE = 1e-3;

static Func *func_list_global = NULL;

/**
 * Create a function with a variable number of arguments.
 *
 * This is at the core of the function system. A function represents a
 * mathematical operation that is evaluated for each audio sample. The function
 * can have any number of inputs, and can be used to create complex audio
 * effects.
 *
 * The function is defined by three callbacks:
 * - init_cb: Called once before the first evaluation. This allows for things like
 *   memory allocation. Typical use cases are functions that keep an internal
 *   buffer like reverb or that open a file like wav.
 * - eval_cb: Returns the value of the function, given inputs and time delta. This
 *   argument is required for all functions. There are no restrictions on the
 *   domain, though for audio functions it is typically in the range [-1, 1].
 * - free_cb: Called once after the last evaluation. This allows for various
 *   cleanup tasks, like deallocating buffers or closing files.
 *
 * Additionally, the function can have a context struct, which is used to store
 * state between evaluations. This is useful for functions that need to keep
 * track of previous values, like a delay line or a filter.
 *
 * The function can have flags that control the behavior of the function. The
 * flags are defined in `def.h` and can be combined with the bitwise OR
 * operator. The default flags are `FuncFlagNone`.
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
 * @param inputs The inputs to the function.
 * @return The function output.
 */
Func *func_create(init_callback init_cb, eval_callback eval_cb, free_callback free_cb, size_t size, void *context, uint32_t flags, size_t count, Func **inputs)
{
    void *initial = NULL;
    if (size > 0 && context != NULL)
    {
        initial = malloc_(size);
        if (initial == NULL)
        {
            return error_null(csErrorMemoryAlloc);
        }
    }
    if (initial != NULL)
    {
        if (context != NULL)
        {
            memcpy(initial, context, size);
        }
        else
        {
            memset(initial, 0, size);
        }
    }
    Func **args = NULL;
    if (count > 0)
    {
        args = (Func **)malloc_(count * sizeof(Func *));
        if (args == NULL)
        {
            free_(initial);
            return error_null(csErrorMemoryAlloc);
        }
        memcpy(args, inputs, count * sizeof(Func *));
    }
    Func *func = (Func *)malloc_(sizeof(Func));
    if (func == NULL)
    {
        free_(initial);
        free_(args);
        return error_null(csErrorMemoryAlloc);
    }
    *func = (Func){
        .args = args,
        .count = count,
        .size = size,
        .initial = initial,
        .init_cb = init_cb,
        .eval_cb = eval_cb,
        .free_cb = free_cb,
        .flags = flags,
        .next = func_list_global,
    };
    func_list_global = func;
    return func;
}

void func_free()
{
    while (func_list_global != NULL)
    {
        Func *func = func_list_global;
        func_list_global = func->next;
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

size_t func_list_size()
{
    size_t size = 0;
    for (Func *func = func_list_global; func; func = func->next)
    {
        size++;
    }
    return size;
}

#endif // CSYNTH_FUNC_H
