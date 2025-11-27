#ifndef CSYNTH_TEST_H
#define CSYNTH_TEST_H

#include <assert.h>
#include <float.h>
#include <stdio.h>

#include "../../src/core/gen.h"

#define long_equal(_a, _b) ((_a) == (_b))
#define double_equal(_a, _b) ((_a) - (_b) < 4 * DBL_EPSILON && (_b) - (_a) < 4 * DBL_EPSILON)
#define double_range(_a, _b, _c) ((_a) >= (_b) && (_a) <= (_c))
#define complex_equal(_a, _b) ((creal(_a) - creal(_b) < 4 * DBL_EPSILON && cimag(_a) - cimag(_b) < 4 * DBL_EPSILON))

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
            fprintf(stdout, "assert(abs(%.16f - %.16f) < 4 * DBL_EPSILON)\n", __a, __b); \
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

#define assert_complex_equal(_a, _b)                                                                                                             \
    do                                                                                                                                           \
    {                                                                                                                                            \
        double __a = (_a), __b = (_b);                                                                                                           \
        if (!complex_equal(__a, __b))                                                                                                            \
        {                                                                                                                                        \
            fprintf(stdout, "assert(abs((%.16f+%.16fi) - (%.16f+%.16fi)) < 4 * DBL_EPSILON)\n", creal(__a), cimag(__a), creal(__b), cimag(__b)); \
        }                                                                                                                                        \
        assert(complex_equal(__a, __b));                                                                                                         \
    } while (0)

#define assert_null(_a)                                   \
    do                                                    \
    {                                                     \
        void *__a = (void *)(_a);                         \
        if (__a != NULL)                                  \
        {                                                 \
            fprintf(stdout, "assert(%p == NULL)\n", __a); \
        }                                                 \
        assert(__a == NULL);                              \
    } while (0)

#define assert_not_null(_a)                               \
    do                                                    \
    {                                                     \
        void *__a = (void *)(_a);                         \
        if (__a == NULL)                                  \
        {                                                 \
            fprintf(stdout, "assert(%p != NULL)\n", __a); \
        }                                                 \
        assert(__a != NULL);                              \
    } while (0)

#define assert_ptr_equal(_a, _b)                             \
    do                                                       \
    {                                                        \
        void *__a = (_a), *__b = (_b);                       \
        if (__a != __b)                                      \
        {                                                    \
            fprintf(stdout, "assert(%p == %p)\n", __a, __b); \
        }                                                    \
        assert(__a == __b);                                  \
    } while (0)

#define assert_ptr_unequal(_a, _b)                           \
    do                                                       \
    {                                                        \
        void *__a = (_a), *__b = (_b);                       \
        if (__a == __b)                                      \
        {                                                    \
            fprintf(stdout, "assert(%p != %p)\n", __a, __b); \
        }                                                    \
        assert(__a != __b);                                  \
    } while (0)

#define assert_string_equal(_a, _b)                                  \
    do                                                               \
    {                                                                \
        const char *__a = (_a), *__b = (_b);                         \
        if (__a == NULL || __b == NULL || strcmp(__a, __b) != 0)     \
        {                                                            \
            fprintf(stdout, "assert(\"%s\" == \"%s\")\n", __a, __b); \
        }                                                            \
        assert(__a != NULL && __b != NULL && strcmp(__a, __b) == 0); \
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
    assert_long_equal(1, 1);
    assert_double_equal(1.0, 1.0);
    assert_double_equal(1.0, 1.0000000000000001);
    assert_double_equal(1.0, 0.9999999999999999);
    assert_double_range(1.0, 1.0, 1.0);
    assert_double_range(0.0, 0.0, 1.0);
    assert_double_range(1.0, 0.0, 1.0);
    assert_null(NULL);
    assert_not_null(&test);
    assert_ptr_equal(&test, &test);
    assert_ptr_unequal(&test, &print_assert_gen_equal);
    assert_string_equal("test", "test");
    int test = 1;
    assert_msg(test == 1, "1 == 1");
}

#endif // CSYNTH_TEST_H
