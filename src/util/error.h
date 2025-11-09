#ifndef CSYNTH_ERROR_H
#define CSYNTH_ERROR_H

#include <stdio.h>
#include <string.h>

#include "./logger.h"

typedef enum
{
    csErrorNone = 0,
    csErrorSome = -1,
    csErrorMemoryAlloc = -2,
    csErrorInvalidArgument = -3,
    csErrorFiniteValue = -4,
    csErrorFileOpen = -5,
    csErrorFileClose = -6,
    csErrorFileRead = -7,
    csErrorFileWrite = -8,
    csErrorFileSeek = -9,
    csErrorInit = -10,
    csErrorNotFound = -11,
    csErrorAudio = -12,
    csErrorMidi = -13,
    csErrorWav = -14,
    csErrorDisplay = -15,
    csErrorPortAudio = -16,
    csErrorPortMidi = -17,
    csErrorThread = -18,
    csErrorLength = -19,
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
    case csErrorThread:
        return "thread error";
    default:
        return "unknown error";
    }
}

#define error_type_message(__type, ...) (log_error(__VA_ARGS__), (__type))
#define error_null_message(__type, ...) (log_error(__VA_ARGS__), NULL)
#define error_catch_message(__type, ...) (void)((__type) != csErrorNone && log_error_expr(__VA_ARGS__))

#define error_type(__type) error_type_message(__type, error_message(__type))
#define error_null(__type) error_null_message(__type, error_message(__type))
#define error_catch(__type) error_catch_message(__type, error_message(__type))

#endif // CSYNTH_ERROR_H
