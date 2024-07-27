#ifndef CSYNTH_ALLOC_H
#define CSYNTH_ALLOC_H

#include <stdio.h>
#include <stdlib.h>

#ifdef ALLOC_TRACE

#define ALLOC_S1(__str) #__str
#define ALLOC_S2(__str) ALLOC_S1(__str)
#define ALLOC_LINE __FILE__ ":" ALLOC_S2(__LINE__)

/**
 * @brief Memory allocation tracking.
 *
 * To find leaks, prefix source with: #define ALLOC_TRACE To log allocations,
 * add: #define ALLOC_LOG
 */
typedef struct Alloc
{
    size_t size;
    const void *ptr;
    const char *line;
    struct Alloc *next;
} Alloc;

typedef struct
{
    size_t alloc_count;
    size_t alloc_size;
    size_t free_count;
    size_t free_size;
} AllocStat;

static Alloc *alloc_list_global = NULL;
static size_t alloc_remove_count = 0;
static size_t alloc_remove_size = 0;

int alloc_list_add(const void *ptr, size_t size, const char *line)
{
    Alloc *alloc = (Alloc *)malloc(sizeof(Alloc));
    if (alloc == NULL)
    {
        return -1;
    }
    alloc->ptr = ptr;
    alloc->size = size;
    alloc->line = line;
    alloc->next = alloc_list_global;
    alloc_list_global = alloc;
    return 0;
}

int alloc_list_remove(const void *ptr)
{
    Alloc **prev = &alloc_list_global;
    for (Alloc *alloc = alloc_list_global; alloc; alloc = alloc->next)
    {
        if (alloc->ptr == ptr)
        {
            *prev = alloc->next;
            alloc_remove_count++;
            alloc_remove_size += alloc->size;
            free(alloc);
            return 0;
        }
        prev = &alloc->next;
    }
    return -1;
}

Alloc *alloc_list_find(const void *ptr)
{
    for (Alloc *alloc = alloc_list_global; alloc; alloc = alloc->next)
    {
        if (alloc->ptr == ptr)
        {
            return alloc;
        }
    }
    return NULL;
}

AllocStat alloc_stat(void)
{
    size_t count = 0;
    size_t size = 0;
    for (Alloc *alloc = alloc_list_global; alloc; alloc = alloc->next)
    {
        count++;
        size += alloc->size;
    }
    return (AllocStat){
        .alloc_count = count,
        .alloc_size = size,
        .free_count = alloc_remove_count,
        .free_size = alloc_remove_size,
    };
}

size_t alloc_size(void)
{
    size_t size = 0;
    for (Alloc *alloc = alloc_list_global; alloc; alloc = alloc->next)
    {
        size += alloc->size;
    }
    return size;
}

int alloc_list_is_empty(void)
{
    return alloc_list_global == NULL;
}

void alloc_list_clear(void)
{
    while (alloc_list_global)
    {
        Alloc *next = alloc_list_global->next;
        free(alloc_list_global);
        alloc_list_global = next;
    }
}

void alloc_list_dump(void)
{
    for (Alloc *alloc = alloc_list_global; alloc; alloc = alloc->next)
    {
        fprintf(stderr, "allocated: %zu bytes, at %s\n", alloc->size, alloc->line);
    }
}

void *alloc_malloc(size_t size, const char *line)
{
    void *ptr = malloc(size);
#ifdef ALLOC_LOG
    fprintf(stderr, "malloc: %p, %zu bytes, at %s\n", ptr, size, line);
#endif
    if (ptr != NULL && alloc_list_add(ptr, size, line))
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
    if (ptr != NULL && alloc_list_add(ptr, count * size, line))
    {
        fprintf(stderr, "calloc error: internal malloc failed, at %s\n", line);
    }
    return ptr;
}

void *alloc_realloc(void *ptr, size_t size, const char *line)
{
    if (ptr != NULL && alloc_list_remove(ptr))
    {
        fprintf(stderr, "realloc error: pointer not allocated %p, at %s\n", ptr, line);
    }
    void *new_ptr = realloc(ptr, size);
#ifdef ALLOC_LOG
    if (ptr != NULL)
    {
        Alloc *alloc = alloc_list_find(ptr);
        if (alloc != NULL)
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
    if (new_ptr != NULL && alloc_list_add(new_ptr, size, line))
    {
        fprintf(stderr, "realloc error: internal realloc failed, at %s\n", line);
    }
    return new_ptr;
}

void alloc_free(void *ptr, const char *line)
{
#ifdef ALLOC_LOG
    if (ptr != NULL)
    {
        Alloc *alloc = alloc_list_find(ptr);
        if (alloc != NULL)
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
    if (ptr != NULL && alloc_list_remove(ptr))
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
