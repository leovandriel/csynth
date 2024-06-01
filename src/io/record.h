//
// record.h - Records key presses and writes to file.
//
#ifndef CSYNTH_RECORD_H
#define CSYNTH_RECORD_H

#include <string.h>
#include <stdio.h>
#include <sys/time.h>

#include "../event/event.h"
#include "../event/key_event.h"

typedef int (*record_callback)(int key, int time, void *context);

typedef struct
{
    int start;
    record_callback callback;
    void *context;
} RecordContext;

int record_clock()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

int record_event_listen(EventType type, void *event_, void *context_)
{
    RecordContext *context = (RecordContext *)context_;
    if (type == EventTypeKey)
    {
        KeyEvent *event = (KeyEvent *)event_;
        double time = record_clock() - context->start;
        context->callback(event->key, time, context->context);
    }
    return 0;
}

void record_with_callback(record_callback callback, void *context_)
{
    RecordContext *context = (RecordContext *)calloc(1, sizeof(RecordContext));
    context->start = record_clock();
    context->callback = callback;
    context->context = context_;
    event_add_listener(record_event_listen, context);
}

int record_file_callback(int key, int time, void *context)
{
    FILE *file = (FILE *)context;
    int err = fprintf(file, "%d %d\n", key, time);
    if (err < 0)
    {
        return err;
    }
    return fflush(file);
}

int record(const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        return -1;
    }
    record_with_callback(record_file_callback, file);
    return 0;
}

#endif // CSYNTH_RECORD_H
