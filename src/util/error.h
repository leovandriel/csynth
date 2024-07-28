#ifndef CSYNTH_ERROR_H
#define CSYNTH_ERROR_H

#include <stdio.h>
#include <string.h>

#include "./logger.h"

typedef enum
{
    csErrorNone = 0,
    csErrorSome,
    csErrorMemoryAlloc,
    csErrorFiniteValue,
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
    csErrorDisplay,
    csErrorPortAudio,
    csErrorPortMidi,
    csErrorLength,
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
    case csErrorFiniteValue:
        return "value is not a finite";
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
    case csErrorDisplay:
        return "Display error";
    case csErrorPortAudio:
        return "PortAudio error";
    case csErrorPortMidi:
        return "PortMIDI error";
    default:
        return "unknown error";
    }
}

#define error_type_message(__type, ...) (log_warn(__VA_ARGS__), (__type))
#define error_null_message(__type, ...) (log_warn(__VA_ARGS__), NULL)
#define error_catch_message(__type, ...) (void)((__type) != csErrorNone && log_error_expr(__VA_ARGS__))

#define error_type(__type) error_type_message(__type, error_message(__type))
#define error_null(__type) error_null_message(__type, error_message(__type))
#define error_catch(__type) error_catch_message(__type, error_message(__type))

#endif // CSYNTH_ERROR_H
