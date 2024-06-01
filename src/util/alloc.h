//
// alloc.h - Allocation utilities
//
#ifndef CSYNTH_ALLOC_H
#define CSYNTH_ALLOC_H

#include <stdlib.h>
#include <stdio.h>

int alloc_ensure(void **array, size_t *capacity, size_t required, size_t element_size)
{
    if (required > *capacity)
    {
        *capacity = required > 8 ? required * 2 : 16;
        void *resized = realloc(*array, *capacity * element_size);
        if (!resized)
        {
            fprintf(stderr, "ensure_capacity: realloc failed\n");
            return 1;
        }
        *array = resized;
    }
    return 0;
}

#endif // CSYNTH_ALLOC_H
