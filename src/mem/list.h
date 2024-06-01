//
// list.h - Dynamic resizing list
//
#ifndef CSYNTH_LIST_H
#define CSYNTH_LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    void *array;
    size_t element;
    size_t capacity;
    size_t size;
} List;

List *list_alloc(size_t element)
{
    List *list = (List *)calloc(1, sizeof(List));
    if (!list)
    {
        fprintf(stderr, "list_create: malloc failed\n");
        return NULL;
    }
    list->element = element;
    return list;
}

void list_free(List *list)
{
    free(list->array);
    free(list);
}

int list_ensure(List *list, size_t initial)
{
    if (list->size == list->capacity)
    {
        list->capacity = list->capacity ? list->capacity * 2 : initial;
        void *resized = realloc(list->array, list->capacity * list->element);
        if (!resized)
        {
            fprintf(stderr, "list_ensure: realloc failed\n");
            return -1;
        }
        memset(resized + list->size * list->element, 0, (list->capacity - list->size) * list->element);
        list->array = resized;
    }
    return 0;
}

int list_add(List *list, void *element)
{
    int err = list_ensure(list, 16);
    if (err)
    {
        return err;
    }
    memcpy(list->array + list->size * list->element, element, list->element);
    list->size++;
    return 0;
}

void *list_get(List *list, size_t index)
{
    if (index < 0 || index >= list->size)
    {
        fprintf(stderr, "list_get: index out of bounds\n");
        return NULL;
    }
    return list->array + index * list->element;
}

size_t list_len(List *list)
{
    return list->size;
}

#endif // CSYNTH_LIST_H
