#ifndef CSYNTH_FILE_H
#define CSYNTH_FILE_H

#include <stdio.h>
#include <stdlib.h>

#ifdef FILE_TRACE

#define FILE_S1(__str) #__str
#define FILE_S2(__str) FILE_S1(__str)
#define FILE_LINE __FILE__ ":" FILE_S2(__LINE__)

/**
 * @brief File open/close tracking.
 *
 * To find unclosed files, prefix source with: #define FILE_TRACE. To log file open/close,
 * add: #define FILE_LOG
 */
typedef struct File
{
    const FILE *ptr;
    const char *name;
    const char *mode;
    const char *line;
    struct File *next;
} File;

typedef struct
{
    size_t open_count;
    size_t close_count;
} FileStat;

static File *file_list_global = NULL;
static size_t file_remove_count = 0;

int file_list_add(const FILE *ptr, const char *name, const char *mode, const char *line)
{
    File *file = (File *)malloc(sizeof(File));
    if (file == NULL)
    {
        return -1;
    }
    file->ptr = ptr;
    file->name = name;
    file->mode = mode;
    file->line = line;
    file->next = file_list_global;
    file_list_global = file;
    return 0;
}

int file_list_remove(const FILE *ptr)
{
    File **prev = &file_list_global;
    for (File *file = file_list_global; file; file = file->next)
    {
        if (file->ptr == ptr)
        {
            *prev = file->next;
            file_remove_count++;
            free(file);
            return 0;
        }
        prev = &file->next;
    }
    return -1;
}

File *file_list_find(const FILE *ptr)
{
    for (File *file = file_list_global; file; file = file->next)
    {
        if (file->ptr == ptr)
        {
            return file;
        }
    }
    return NULL;
}

FileStat file_stat(void)
{
    size_t count = 0;
    for (File *file = file_list_global; file; file = file->next)
    {
        count++;
    }
    return (FileStat){
        .open_count = count,
        .close_count = file_remove_count,
    };
}

size_t file_count(void)
{
    size_t count = 0;
    for (File *file = file_list_global; file; file = file->next)
    {
        count++;
    }
    return count;
}

int file_list_is_empty(void)
{
    return file_list_global == NULL;
}

void file_list_clear(void)
{
    while (file_list_global)
    {
        File *next = file_list_global->next;
        free(file_list_global);
        file_list_global = next;
    }
}

void file_list_dump(void)
{
    for (File *file = file_list_global; file; file = file->next)
    {
        fprintf(stderr, "opened: %s, mode %s, at %s\n", file->name, file->mode, file->line);
    }
}

void *file_open(const char *filename, const char *mode, const char *line)
{
    FILE *ptr = fopen(filename, mode);
#ifdef FILE_LOG
    fprintf(stderr, "fopen: %p, %s, mode %s, at %s\n", ptr, filename, mode, line);
#endif
#pragma GCC diagnostic push
#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif
    if (ptr != NULL && file_list_add(ptr, filename, mode, line))
#pragma GCC diagnostic pop
    {
        fprintf(stderr, "fopen error: internal open failed, at %s\n", line);
    }
    return ptr;
}

FILE *file_memopen(void *buffer, size_t size, const char *mode, const char *line)
{
    FILE *ptr = fmemopen(buffer, size, mode);
#ifdef FILE_LOG
    fprintf(stderr, "fmemopen: %p, %p, %ud, mode %s, at %s\n", ptr, buffer, size, mode, line);
#endif
#pragma GCC diagnostic push
#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif
    if (ptr != NULL && file_list_add(ptr, "in-memory", mode, line))
#pragma GCC diagnostic pop
    {
        fprintf(stderr, "fopen error: internal open failed, at %s\n", line);
    }
    return ptr;
}

int file_close(FILE *ptr, const char *line)
{
#ifdef FILE_LOG
    if (ptr != NULL)
    {
        File *file = file_list_find(ptr);
        if (file != NULL)
        {
            fprintf(stderr, "fclose: %p, %s, mode %s, from %s, at %s\n", ptr, file->name, file->mode, file->line, line);
        }
        else
        {
            fprintf(stderr, "fclose: %p, ??, mode ??, from ??, at %s\n", ptr, line);
        }
    }
    else
    {
        fprintf(stderr, "fclose: %p, NULL pointer, at %s\n", ptr, line);
    }
#endif
    if (ptr != NULL && file_list_remove(ptr))
    {
        fprintf(stderr, "fclose error: file not open %p, at %s\n", ptr, line);
    }
    return fclose(ptr);
}

#define fopen_(__filename, __mode) file_open(__filename, __mode, FILE_LINE)
#define fmemopen_(__buffer, __size, __mode) file_memopen(__buffer, __size, __mode, FILE_LINE)
#define fclose_(__file) file_close(__file, FILE_LINE)

#else // FILE_TRACE

#define fopen_(__filename, __mode) fopen(__filename, __mode)
#define fmemopen_(__buffer, __size, __mode) fmemopen(__buffer, __size, __mode)
#define fclose_(__file) fclose(__file)

#endif // FILE_TRACE

#endif // CSYNTH_FILE_H
