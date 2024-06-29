//
// def.h - Core definitions.
//
#ifndef CSYNTH_DEF_H
#define CSYNTH_DEF_H

#include <stddef.h>

#define __U __attribute__((unused))

#define ARRAY(__type, ...) ((__type[]){__VA_ARGS__})
#define ARRAY_SIZE(__array) (sizeof((__array)) / sizeof((__array)[0]))
#define ARRAY_ARGS(__array) ARRAY_SIZE(__array), (__array)
#define FUNCS(...) ARRAY_ARGS(ARRAY(Func *, __VA_ARGS__))

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
    EvalStepAudio = 0,
    EvalStepControl = 1,
    EvalStepLength // last
} EvalStep;

typedef struct
{
    double step[EvalStepLength];
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
