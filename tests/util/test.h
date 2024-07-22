//
// test.h - Testing utilties
//
#ifndef CSYNTH_TEST_H
#define CSYNTH_TEST_H

#include <assert.h>
#include <float.h>
#include <stdio.h>

#include "../../src/core/gen.h"

#define long_equal(_a, _b) ((_a) == (_b))
#define double_equal(_a, _b) ((_a) - (_b) < 2 * DBL_EPSILON && (_b) - (_a) < 2 * DBL_EPSILON)
#define double_range(_a, _b, _c) ((_a) >= (_b) && (_a) <= (_c))

#define assert_long_equal(_a, _b)                              \
    do                                                         \
    {                                                          \
        long __a = (_a), __b = (_b);                           \
        if (!long_equal(__a, __b))                             \
        {                                                      \
            fprintf(stdout, "assert(%ld == %ld)\n", __a, __b); \
        }                                                      \
        assert(long_equal(__a, __b));                          \
    } while (0)

#define assert_double_equal(_a, _b)                                                      \
    do                                                                                   \
    {                                                                                    \
        double __a = (_a), __b = (_b);                                                   \
        if (!double_equal(__a, __b))                                                     \
        {                                                                                \
            fprintf(stdout, "assert(abs(%.16f - %.16f) < 2 * DBL_EPSILON)\n", __a, __b); \
        }                                                                                \
        assert(double_equal(__a, __b));                                                  \
    } while (0)

#define assert_double_range(_a, _b, _c)                                                        \
    do                                                                                         \
    {                                                                                          \
        double __a = (_a), __b = (_b), __c = (_c);                                             \
        if (!double_range(__a, __b, __c))                                                      \
        {                                                                                      \
            fprintf(stdout, "assert(%.16f >= %.16f && %.16f <= %.16f)\n", __a, __b, __a, __c); \
        }                                                                                      \
        assert(double_range(__a, __b, __c));                                                   \
    } while (0)

#define assert_msg(_cond, _msg)            \
    do                                     \
    {                                      \
        if (!(_cond))                      \
        {                                  \
            fprintf(stderr, "%s\n", _msg); \
        }                                  \
        assert(_cond);                     \
    } while (0)

void print_assert_gen_equal(Gen *gen, Eval *eval)
{
    fprintf(stdout, "\n");
    for (size_t i = 0; i < 12; i++)
    {
        fprintf(stdout, "    assert_double_equal(gen_eval(gen, NULL), %.16f);\n", gen_eval(gen, eval));
    }
    fprintf(stdout, "\n");
}

void test(void)
{
}

#endif // CSYNTH_TEST_H
