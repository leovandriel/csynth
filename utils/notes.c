//usr/bin/gcc "$0" -o bin/notes -Wall -Wextra -O3 -lm && ./bin/notes "$@"; exit $?
//
//  Generates contents for the `notes.h` file.
//
#include <math.h>
#include <stdio.h>

static const char *note_names[] = {"C", "Cs", "Db", "D", "Ds", "Eb", "E", "F", "Fs", "Gb", "G", "Gs", "Ab", "A", "As", "Bb", "B"};

void main()
{
    int octaves = 10;
    for (int i = 0; i < 17 * octaves; i++)
    {
        const char *note = note_names[i % 17];
        int octave = i / 17;
        int index = (int)((i + 4) * 12.0 / 17 - 59.45);
        double freq = 440 * pow(2, index / 12.0);
        int prec = 20 - log10(freq);
        fprintf(stderr, "static const double %s%d_ = %.*f; // 440 * pow(2, %d / 12.0)\n", note, octave, prec, freq, index);
    }
    for (int i = 0; i < 17 * octaves; i++)
    {
        const char *note = note_names[i % 17];
        int octave = i / 17;
        fprintf(stderr, "#define %s%d (const_(%s%d_))\n", note, octave, note, octave);
    }
}
