//
// def.h - Core definitions.
//
#ifndef CSYNTH_DEF_H
#define CSYNTH_DEF_H

typedef struct Func Func;
typedef Func *func;
typedef struct Gen Gen;

#define FUNC_FLAG_DEFAULT (0)
#define FUNC_FLAG_NO_RESET (1 << 1)

typedef double (*eval_cb)(int count, Gen **args, double delta, void *context);
typedef void (*init_cb)(int count, Gen **args, double delta, void *context);
typedef void (*free_cb)(void *context);

// Represents a function (R -> Rn) that takes one or more inputs and outputs a single value.
struct Func
{
    Func **args;
    int count;
    size_t size;
    void *initial;
    init_cb init;
    eval_cb eval;
    free_cb free;
    unsigned int flags;
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
