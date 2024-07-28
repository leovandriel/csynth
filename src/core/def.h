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
    EvalParamNone = 0,
    EvalParamControlTick,
    EvalParamDisplayTick,
    EvalParamPitchTick,
    EvalParamTempoTick,
    EvalParamSustainTick,
    EvalParamLength // last
} EvalParam;

/**
 * @brief Evaluation state, passed in the generator by the sampler.
 */
typedef struct
{
    /** @brief Wall time in seconds. */
    double wall_time;
    /** @brief Wall time delta, in seconds. */
    double wall_tick;
    /** @brief Compute time in seconds. */
    double compute_time;
    /** @brief Compute time delta, in seconds. */
    double compute_tick;
    /** @brief Flag indicating this round expensive computation can be done. */
    bool compute_flag;
    /** @brief Parameters for evaluation, i.e. variable passed upstream. */
    double params[EvalParamLength];
    /** @brief Generation counter. */
    size_t gen_count;
} Eval;

typedef double (*eval_callback)(size_t count, Gen **args, Eval *eval, void *context);
typedef int (*init_callback)(size_t count, Gen **args, void *context);
typedef void (*free_callback)(size_t count, void *context);

/**
 * @brief Represents a function (R -> Rn) that takes one or more inputs and
 * outputs a single value.
 */
struct Func
{
    /** @brief Function arguments. */
    Func **args;
    /** @brief Function argument count. */
    size_t count;
    /** @brief Function context size. */
    size_t size;
    /** @brief Function context initial value, used for reset. */
    void *initial;
    /** @brief Invoked once during initialization. */
    init_callback init_cb;
    /** @brief Invoked for every eval cycle, i.e. for every sample. */
    eval_callback eval_cb;
    /** @brief Invoked once during cleanup. */
    free_callback free_cb;
    /** @brief Function flags. */
    uint32_t flags;
    /** @brief Next function in linked list. */
    Func *next;
    /** @brief Function name, for display in func tool. */
    const char *name;
    /** @brief Function arguments names, separated by comma. */
    const char *arg_names;
};

/**
 * @brief Generator, representing an evaluation instance of a function.
 */
struct Gen
{
    /** @brief Function to sample. */
    Func *func;
    /** @brief Function input arguments. */
    Gen **args;
    /** @brief Function context, to be passed in during evaluation. */
    void *context;
    /** @brief The state to which to restore context upon reset. */
    void *reset;
};

#endif // CSYNTH_DEF_H
