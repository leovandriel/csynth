#ifndef CSYNTH_NOTE_H
#define CSYNTH_NOTE_H

#include <math.h>
#include <stddef.h>
#include <stdio.h>

static const char *NOTE_NAMES[] = {"C", "", "D", "", "E", "F", "", "G", "", "A", "", "B"};
static const char *NOTE_SUFFIXES[] = {"s", "", "b"};

double note_frequency_to_index(double frequency)
{
    return log2(frequency / 440) * 12.0 + 57.0;
}

int note_ij_to_string(int i, int j, char *buffer, size_t size)
{
    const char *note = NOTE_NAMES[i % 12 + j];
    const char *suffix = NOTE_SUFFIXES[1 + j];
    int octave = i / 12;
    return snprintf(buffer, size, "%s%s%d", note, suffix, octave);
}

int note_index_to_string(double index, char *buffer, size_t size)
{
    int i = floor(index + 0.5);
    int j = !NOTE_NAMES[i % 12][0] * (index > i ? 1 : -1);
    return note_ij_to_string(i, j, buffer, size);
}

#endif // CSYNTH_NOTE_H
