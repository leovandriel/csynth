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

int key_list_add(KeyList *list, TimedKeyboardEvent event)
{
    TimedKeyboardEvent *new_event = malloc_(sizeof(TimedKeyboardEvent));
    if (!new_event)
    {
        return -1;
    }
    *new_event = event;
    new_event->next = *list;
    *list = new_event;
    return 0;
}

int key_list_clear(KeyList *list)
{
    while (*list)
    {
        TimedKeyboardEvent *next = (*list)->next;
        free_(*list);
        *list = next;
    }
    return 0;
}

int key_list_read_file(KeyList *list, FILE *file)
{
    int key = 0;
    int stamp = 0;
    while (fscanf(file, "%d %d\n", &key, &stamp) == 2)
    {
        TimedKeyboardEvent event = {.key = key, .time = stamp / 1000.0};
        int err = key_list_add(list, event);
        if (err)
        {
            return err;
        }
    }
    return 0;
}

int key_list_read_filename(KeyList *list, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        fprintf(stderr, "record: failed to open file %s\n", filename);
        return -1;
    }
    int err = key_list_read_file(list, file);
    fclose(file);
    return err;
}

int key_list_write_file(KeyList *list, FILE *file)
{
    for (TimedKeyboardEvent *event = *list; event; event = event->next)
    {
        int err = fprintf(file, "%d %d\n", event->key, (int)(event->time * 1000));
        if (err < 0)
        {
            fprintf(stderr, "record: failed to write to file\n");
            return -1;
        }
    }
    return 0;
}

int key_list_write_filename(KeyList *list, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        fprintf(stderr, "record: failed to open file %s\n", filename);
        return -1;
    }
    int err = key_list_write_file(list, file);
    fclose(file);
    return err;
}

#endif // CSYNTH_KEY_LIST_H
