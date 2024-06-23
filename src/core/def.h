//
// def.h - Core definitions.
//
#ifndef CSYNTH_DEF_H
#define CSYNTH_DEF_H

#include <stddef.h>

typedef struct Func Func;
typedef Func *func;
typedef struct Gen Gen;

#define FUNC_FLAG_DEFAULT (0)
#define FUNC_FLAG_STOP_RESET (1 << 1)
#define FUNC_FLAG_SKIP_RESET (1 << 2)
#define __U __attribute__((unused))

typedef double (*eval_callback)(int count, Gen **args, double delta, void *context);
typedef int (*init_callback)(int count, Gen **args, double delta, void *context);
typedef void (*free_callback)(int count, void *context);

// Represents a function (R -> Rn) that takes one or more inputs and outputs a single value.
struct Func
{
    Func **args;
    int count;
    size_t size;
    void *initial;
    init_callback init_cb;
    eval_callback eval_cb;
    free_callback free_cb;
    unsigned int flags;
    Func *next;
};

struct Gen
{
    Func *func;
    Gen **args;
    double delta;
    void *context;
    void *reset;
};

#endif // CSYNTH_DEF_H
