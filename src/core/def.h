//
// def.h - Core definitions.
//
#ifndef CSYNTH_DEF_H
#define CSYNTH_DEF_H

#include <stddef.h>

#define __U __attribute__((unused))

typedef struct Func Func;
typedef Func *func;
typedef struct Gen Gen;

typedef enum
{
    FuncFlagNone = 0,
    FuncFlagStopReset = 1 << 1,
    FuncFlagSkipReset = 1 << 2,
} FuncFlag;

typedef enum
{
    EvalTickPitch,
    EvalTickTempo,
    EvalTickSustain,
    EvalTickControl,
    EvalTickDisplay,
    EvalTickLength // last
} EvalTick;

typedef struct
{
    double wall_time;
    double wall_tick;
    double tick[EvalTickLength];
} Eval;

typedef double (*eval_callback)(int count, Gen **args, Eval eval, void *context);
typedef int (*init_callback)(int count, Gen **args, void *context);
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
    void *context;
    void *reset;
};

#endif // CSYNTH_DEF_H
