//
// def.h - Core definitions.
//
#ifndef CSYNTH_DEF_H
#define CSYNTH_DEF_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

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
    EvalTickNone = 0,
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
    size_t gen_count;
    size_t error_count;
} Eval;

typedef double (*eval_callback)(size_t count, Gen **args, Eval *eval, void *context);
typedef bool (*init_callback)(size_t count, Gen **args, void *context);
typedef void (*free_callback)(size_t count, void *context);

// Represents a function (R -> Rn) that takes one or more inputs and outputs a single value.
struct Func
{
    Func **args;
    size_t count;
    size_t size;
    void *initial;
    init_callback init_cb;
    eval_callback eval_cb;
    free_callback free_cb;
    uint32_t flags;
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
