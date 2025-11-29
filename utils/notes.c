//usr/bin/gcc "$0" -o bin/notes -Wall -Wextra -O3 -lm && ./bin/notes "$@"; exit $?
#include <math.h>
#include <stdio.h>

#include "../src/util/note.h"

int main(void)
{
    int octaves = 10;
    for (int i = 0; i < 12 * octaves; i++)
    {
        for (int j = -!NOTE_NAMES[i % 12][0]; j <= 1; j += 2)
        {
            char note[4];
            note_ij_to_string(i, j, note, 4);
            int index = i - 57;
            double freq = 440 * pow(2, index / 12.0);
            int prec = 19 - (int)log10(freq);
            fprintf(stdout, "#define %s_ %.*f // 440 * pow(2, %d / 12.0)\n", note, prec, freq, index);
        }
    }

    fprintf(stdout, "\n");

    for (int i = 0; i < 12 * octaves; i++)
    {
        for (int j = -!NOTE_NAMES[i % 12][0]; j <= 1; j += 2)
        {
            char note[4];
            note_ij_to_string(i, j, note, 4);
            fprintf(stdout, "#define %s (const_(%s_))\n", note, note);
        }
    }
}
