//
// key_list.h - Timed sequence of key events.
//
#ifndef CSYNTH_KEY_LIST_H
#define CSYNTH_KEY_LIST_H

#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#include "../event/event.h"
#include "../event/keyboard_event.h"

typedef struct TimedKeyboardEvent
{
    double time;
    int key;
    struct TimedKeyboardEvent *next;
} TimedKeyboardEvent;

typedef TimedKeyboardEvent *KeyList;

csError key_list_add(KeyList *list, TimedKeyboardEvent event)
{
    TimedKeyboardEvent *new_event = malloc_(sizeof(TimedKeyboardEvent));
    if (new_event == NULL)
    {
        return error_type(csErrorMemoryAlloc);
    }
    *new_event = event;
    new_event->next = *list;
    *list = new_event;
    return csErrorNone;
}

void key_list_clear(KeyList *list)
{
    while (*list)
    {
        TimedKeyboardEvent *next = (*list)->next;
        free_(*list);
        *list = next;
    }
}

csError key_list_read_file(KeyList *list, FILE *file)
{
    int key = 0;
    int stamp = 0;
    while (fscanf(file, "%d %d\n", &key, &stamp) == 2)
    {
        TimedKeyboardEvent event = {.key = key, .time = stamp / 1000.0};
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
    for (TimedKeyboardEvent *event = *list; event; event = event->next)
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
