//
// alloc.h - Memory allocation wrappers
//
// To find leaks, prefix source with: #define ALLOC_TRACE
// To log allocations, add: #define ALLOC_LOG
//
#ifndef CSYNTH_ALLOC_H
#define CSYNTH_ALLOC_H

#include <stdio.h>
#include <stdlib.h>

#ifdef ALLOC_TRACE

#define ALLOC_S1(__str) #__str
#define ALLOC_S2(__str) ALLOC_S1(__str)
#define ALLOC_LINE __FILE__ ":" ALLOC_S2(__LINE__)

typedef struct Alloc
{
    size_t size;
    void *ptr;
    const char *line;
    struct Alloc *next;
} Alloc;

Alloc *alloc_list = NULL;

int alloc_list_add(void *ptr, size_t size, const char *line)
{
    Alloc *alloc = (Alloc *)malloc(sizeof(Alloc));
    if (!alloc)
    {
        return -1;
    }
    alloc->ptr = ptr;
    alloc->size = size;
    alloc->line = line;
    alloc->next = alloc_list;
    alloc_list = alloc;
    return 0;
}

int alloc_list_remove(void *ptr)
{
    Alloc **prev = &alloc_list;
    for (Alloc *iter = alloc_list; iter; iter = iter->next)
    {
        if (iter->ptr == ptr)
        {
            *prev = iter->next;
            free(iter);
            return 0;
        }
        prev = &iter->next;
    }
    return -1;
}

Alloc *alloc_list_find(void *ptr)
{
    for (Alloc *iter = alloc_list; iter; iter = iter->next)
    {
        if (iter->ptr == ptr)
        {
            return iter;
        }
    }
    return NULL;
}

size_t alloc_list_count()
{
    size_t count = 0;
    for (Alloc *iter = alloc_list; iter; iter = iter->next)
    {
        count++;
    }
    return count;
}

int alloc_list_is_empty()
{
    return alloc_list == NULL;
}

void alloc_list_clear()
{
    while (alloc_list)
    {
        Alloc *next = alloc_list->next;
        free(alloc_list);
        alloc_list = next;
    }
}

void alloc_list_dump()
{
    for (Alloc *iter = alloc_list; iter; iter = iter->next)
    {
        fprintf(stderr, "allocated: %zu bytes, at %s\n", iter->size, iter->line);
    }
}

void *alloc_malloc(size_t size, const char *line)
{
    void *ptr = malloc(size);
#ifdef ALLOC_LOG
    fprintf(stderr, "malloc: %p, %zu bytes, at %s\n", ptr, size, line);
#endif
    if (ptr && alloc_list_add(ptr, size, line))
    {
        fprintf(stderr, "malloc error: internal malloc failed, at %s\n", line);
    }
    return ptr;
}

void *alloc_calloc(size_t count, size_t size, const char *line)
{
    void *ptr = calloc(count, size);
#ifdef ALLOC_LOG
    fprintf(stderr, "calloc: %p, %zu bytes, at %s\n", ptr, count * size, line);
#endif
    if (ptr && alloc_list_add(ptr, count * size, line))
    {
        fprintf(stderr, "calloc error: internal malloc failed, at %s\n", line);
    }
    return ptr;
}

void *alloc_realloc(void *ptr, size_t size, const char *line)
{
    if (ptr && alloc_list_remove(ptr))
    {
        fprintf(stderr, "realloc error: pointer not allocated %p, at %s\n", ptr, line);
    }
    void *new_ptr = realloc(ptr, size);
#ifdef ALLOC_LOG
    if (ptr)
    {
        Alloc *alloc = alloc_list_find(ptr);
        if (alloc)
        {
            fprintf(stderr, "realloc: %p to %p, %zu to %zu bytes, from %s, at %s\n", ptr, new_ptr, alloc->size, size, alloc->line, line);
        }
        else
        {
            fprintf(stderr, "realloc: %p to %p, ?? to %zu bytes, from ??, at %s\n", ptr, new_ptr, size, line);
        }
    }
    else
    {
        fprintf(stderr, "realloc: %p to %p, 0 to %zu bytes, at %s\n", ptr, new_ptr, size, line);
    }
#endif
    if (new_ptr && alloc_list_add(new_ptr, size, line))
    {
        fprintf(stderr, "realloc error: internal realloc failed, at %s\n", line);
    }
    return new_ptr;
}

void alloc_free(void *ptr, const char *line)
{
#ifdef ALLOC_LOG
    if (ptr)
    {
        Alloc *alloc = alloc_list_find(ptr);
        if (alloc)
        {
            fprintf(stderr, "free: %p, %zu bytes, from %s, at %s\n", ptr, alloc->size, alloc->line, line);
        }
        else
        {
            fprintf(stderr, "free: %p, ?? bytes, from ??, at %s\n", ptr, line);
        }
    }
    else
    {
        fprintf(stderr, "free: %p, NULL pointer, at %s\n", ptr, line);
    }
#endif
    if (ptr && alloc_list_remove(ptr))
    {
        fprintf(stderr, "free error: pointer not allocated %p, at %s\n", ptr, line);
    }
    free(ptr);
}

#define malloc_(__size) alloc_malloc(__size, ALLOC_LINE)
#define calloc_(__count, __size) alloc_calloc(__count, __size, ALLOC_LINE)
#define free_(__ptr) alloc_free(__ptr, ALLOC_LINE)
#define realloc_(__ptr, __size) alloc_realloc(__ptr, __size, ALLOC_LINE)

#else // ALLOC_TRACE

#define malloc_(__size) malloc(__size)
#define calloc_(__count, __size) calloc(__count, __size)
#define free_(__ptr) free(__ptr)
#define realloc_(__ptr, __size) realloc(__ptr, __size)

#endif // ALLOC_TRACE

#endif // CSYNTH_ALLOC_H
