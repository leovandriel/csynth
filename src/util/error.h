//
// error.h - Error handling
//
#ifndef CSYNTH_ERROR_H
#define CSYNTH_ERROR_H

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

typedef enum
{
    csErrorNone = 0,
    csErrorSome = -32768,
    csErrorMemoryAlloc,
    csErrorFileOpen,
    csErrorFileClose,
    csErrorFileRead,
    csErrorFileWrite,
    csErrorFileSeek,
    csErrorInit,
    csErrorNotFound,
    csErrorAudio,
    csErrorMidi,
    csErrorWav,
    csErrorPortAudio,
    csErrorPortMidi,
} csError;

const char *error_message(csError type)
{
    switch (type)
    {
    case csErrorNone:
        return "no error";
    case csErrorSome:
        return "some error";
    case csErrorMemoryAlloc:
        return "unable to allocate memory";
    case csErrorFileOpen:
        return "unable to open file";
    case csErrorFileClose:
        return "unable to close file";
    case csErrorFileRead:
        return "unable to read file";
    case csErrorFileWrite:
        return "unable to write file";
    case csErrorFileSeek:
        return "unable to seek file";
    case csErrorInit:
        return "unable to initialize";
    case csErrorNotFound:
        return "unable to find";
    case csErrorAudio:
        return "audio error";
    case csErrorMidi:
        return "MIDI error";
    case csErrorWav:
        return "WAV error";
    case csErrorPortAudio:
        return "PortAudio error";
    case csErrorPortMidi:
        return "PortMIDI error";
    default:
        return "unknown error";
    }
}

static void error_report(csError type, const char *file, int line, const char *message, ...)
{
    va_list args = {0};
    va_start(args, message);
    if (type != csErrorNone)
    {
        fprintf(stderr, "error: ");
        vfprintf(stderr, message, args);
        fprintf(stderr, " (%d) at %s:%d \n", type, strrchr(file, '/') + 1, line);
    }
    va_end(args);
}

#define error_type_message(__type, __message, ...) (error_report(__type, "/"__FILE__, __LINE__, __message, ##__VA_ARGS__), (__type))
#define error_null_message(__type, __message, ...) (error_report(__type, "/"__FILE__, __LINE__, __message, ##__VA_ARGS__), NULL)
#define error_catch_message(__type, __message, ...) (error_report(__type, "/"__FILE__, __LINE__, __message, ##__VA_ARGS__), ((__type) != csErrorNone))

#define error_type(__type) error_type_message(__type, error_message(__type))
#define error_null(__type) error_null_message(__type, error_message(__type))
#define error_catch(__type) error_catch_message(__type, error_message(__type))

#endif // CSYNTH_ERROR_H
