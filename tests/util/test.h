//
// test.h - Testing utilties
//
#include <assert.h>
#include <stdio.h>

#include "../../src/core/gen.h"

#define long_equal(_a, _b) ((_a) == (_b))
#define double_equal(_a, _b) ((_a) - (_b) < EPSILON && (_b) - (_a) < EPSILON)
#define double_range(_a, _b, _c) ((_a) >= (_b) && (_a) <= (_c))

#define assert_long_equal(_a, _b)                     \
    do                                                \
    {                                                 \
        long __a = (_a), __b = (_b);                  \
        if (!long_equal(__a, __b))                    \
        {                                             \
            printf("assert(%ld == %ld)\n", __a, __b); \
        }                                             \
        assert(long_equal(__a, __b));                 \
    } while (0)
#define assert_double_equal(_a, _b)                                     \
    do                                                                  \
    {                                                                   \
        double __a = (_a), __b = (_b);                                  \
        if (!double_equal(__a, __b))                                    \
        {                                                               \
            printf("assert(abs(%.16f - %.16f) < EPSILON)\n", __a, __b); \
        }                                                               \
        assert(double_equal(__a, __b));                                 \
    } while (0)
#define assert_double_range(_a, _b, _c)                                               \
    do                                                                                \
    {                                                                                 \
        double __a = (_a), __b = (_b), __c = (_c);                                    \
        if (!double_range(__a, __b, __c))                                             \
        {                                                                             \
            printf("assert(%.16f >= %.16f && %.16f <= %.16f)\n", __a, __b, __a, __c); \
        }                                                                             \
        assert(double_range(__a, __b, __c));                                          \
    } while (0)

#define assert_gen_equal(_gen, _value) assert_double_equal(gen_eval(_gen), _value)
#define assert_gen_range(_gen, _a, _b) assert_double_range(gen_eval(_gen), _a, _b)

void print_assert_gen_equal(Gen *g)
{
    printf("\n");
    for (int i = 0; i < 12; i++)
    {
        printf("    assert_gen_equal(g, %.16f);\n", gen_eval(g));
    }
    printf("\n");
}

void test_test()
{
}
