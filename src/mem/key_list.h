#ifndef CSYNTH_KEY_LIST_H
#define CSYNTH_KEY_LIST_H

#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#include "../event/control_event.h"
#include "../event/event.h"

/**
 * @brief Key stroke event, at a specific time.
 */
typedef struct KeyboardEvent
{
    /** @brief Time in seconds. */
    double time;
    /** @brief Key code. */
    int key;
    /** @brief Next event in the linked list. */
    struct KeyboardEvent *next;
} KeyboardEvent;

/**
 * @brief List of key stroke events.
 */
typedef struct
{
    /** @brief First event in the list. */
    KeyboardEvent *head;
    /** @brief Last event in the list. */
    KeyboardEvent *tail;
} KeyList;

csError key_list_add(KeyList *list, KeyboardEvent event)
{
    KeyboardEvent *new_event = malloc_(sizeof(KeyboardEvent));
    if (new_event == NULL)
    {
        return error_type(csErrorMemoryAlloc);
    }
    *new_event = event;
    if (list->head == NULL)
    {
        list->head = new_event;
        list->tail = new_event;
    }
    else
    {
        list->tail->next = new_event;
        list->tail = new_event;
    }
    return csErrorNone;
}

void key_list_clear(KeyList *list)
{
    while (list->head)
    {
        KeyboardEvent *next = list->head->next;
        free_(list->head);
        list->head = next;
    }
    list->tail = NULL;
}

csError key_list_read_file(KeyList *list, FILE *file)
{
    int key = 0;
    int stamp = 0;
    while (fscanf(file, "%d %d\n", &key, &stamp) == 2)
    {
        KeyboardEvent event = {
            .key = key,
            .time = stamp / 1000.0,
        };
        csError error = key_list_add(list, event);
        if (error != csErrorNone)
        {
            return error;
        }
    }
    return csErrorNone;
}

csError key_list_read_filename(KeyList *list, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        return error_type_message(csErrorFileOpen, "Unable to open file: %s", filename);
    }
    csError error = key_list_read_file(list, file);
    if (error != csErrorNone)
    {
        fclose(file);
        return error;
    }
    if (fclose(file) == EOF)
    {
        return error_type(csErrorFileClose);
    }
    return csErrorNone;
}

csError key_list_write_file(KeyList *list, FILE *file)
{
    for (KeyboardEvent *event = list->head; event; event = event->next)
    {
        int count = fprintf(file, "%d %d\n", event->key, (int)(event->time * 1000));
        if (count < 0)
        {
            return error_type(csErrorFileWrite);
        }
    }
    return csErrorNone;
}

csError key_list_write_filename(KeyList *list, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        return error_type_message(csErrorFileOpen, "Unable to open file: %s", filename);
    }
    csError error = key_list_write_file(list, file);
    if (error != csErrorNone)
    {
        fclose(file);
        return error;
    }
    if (fclose(file) == EOF)
    {
        return error_type(csErrorFileClose);
    }
    return csErrorNone;
}

#endif // CSYNTH_KEY_LIST_H
