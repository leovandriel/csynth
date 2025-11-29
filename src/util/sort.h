#ifndef CSYNTH_SORT_H
#define CSYNTH_SORT_H

#include <stdlib.h>

typedef int (*sort_compare)(const void *a, const void *b, const void *context);

static const void *g_sort_context = NULL;
static sort_compare g_sort_compare = NULL;

static int sort_wrapper(const void *a, const void *b)
{
    return g_sort_compare(a, b, g_sort_context);
}

static inline void sort(void *values, size_t count, size_t size, sort_compare compare, const void *context)
{
    g_sort_compare = compare;
    g_sort_context = context;
    qsort(values, count, size, sort_wrapper);
    g_sort_compare = NULL;
    g_sort_context = NULL;
}

#endif // CSYNTH_SORT_H
