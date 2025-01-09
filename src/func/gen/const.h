#ifndef CSYNTH_CONST_H
#define CSYNTH_CONST_H

#include "../../core/func.h"
#include "../../core/gen.h"

/** @see const_create */
typedef struct
{
    /** @brief Constant value. */
    double value;
} ConstContext;

static double const_eval(__U size_t count, __U Gen **args, __U Eval *eval, void *context_)
{
    ConstContext *context = (ConstContext *)context_;
    return context->value;
}

/**
 * @brief Create a function that outputs a constant value.
 *
 * This function creates a generator that always outputs the same value,
 * regardless of time or other inputs. It is useful for:
 * - Setting fixed parameter values
 * - Creating DC offsets
 * - Testing and debugging
 * - Providing constant modulation values
 *
 * The constant function is one of the simplest generators, with O(1) time
 * complexity since it just returns a stored value.
 *
 * @param value The fixed numerical value that will be output every time the
 *              function is evaluated. Can be any double precision floating
 *              point number.
 * @return Func* A constant function that always returns the specified value.
 */
Func *const_create(double value)
{
    ConstContext initial = {.value = value};
    return func_create(NULL, const_eval, NULL, NULL, sizeof(ConstContext), &initial, FuncFlagNone);
}

/** @brief Shorthand for `const_create`. */
Func *const_(double value) { return const_create(value); }
/** @brief Shorthand for `const_create`. */
Func *_(double value) { return const_(value); }

#endif // CSYNTH_CONST_H
