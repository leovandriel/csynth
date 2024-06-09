//
// key_list.h - Timed sequence of key events.
//
#ifndef CSYNTH_KEY_LIST_H
#define CSYNTH_KEY_LIST_H

#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#include "../event/event.h"
#include "../event/key_event.h"
#include "../mem/list.h"

typedef struct
{
    int key;
    double time;
} TimedKeyEvent;

typedef List KeyList;
KeyList *key_list_alloc() { return list_alloc(sizeof(TimedKeyEvent)); }
void key_list_free(KeyList *list) { list_free(list); }
size_t key_list_len(KeyList *list) { return list_len(list); }
int key_list_add(KeyList *list, TimedKeyEvent event) { return list_add(list, &event); }
TimedKeyEvent key_list_get(KeyList *list, size_t index) { return *(TimedKeyEvent *)list_get(list, index); }

int key_list_read_file(KeyList *list, FILE *file)
{
    int key = 0;
    int stamp = 0;
    while (fscanf(file, "%d %d\n", &key, &stamp) == 2)
    {
        TimedKeyEvent event = {.key = key, .time = stamp / 1000.0};
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
    for (size_t i = 0; i < key_list_len(list); i++)
    {
        TimedKeyEvent event = key_list_get(list, i);
        int err = fprintf(file, "%d %d\n", event.key, (int)(event.time * 1000));
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
