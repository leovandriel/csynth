//
// notes.h - Note constants for 11 octaves.
//
// The contents of this file can be generated using `print_notes_h`.
//
#ifndef CSYNTH_NOTES_H
#define CSYNTH_NOTES_H

#include <assert.h>
#include <math.h>
#include <stdio.h>

#include "./const.h"

#define C0 const_(440 * pow(2, -57 / 12.0))  // 16.35
#define Cs0 const_(440 * pow(2, -56 / 12.0)) // 17.32
#define Db0 const_(440 * pow(2, -56 / 12.0)) // 17.32
#define D0 const_(440 * pow(2, -55 / 12.0))  // 18.35
#define Ds0 const_(440 * pow(2, -54 / 12.0)) // 19.45
#define Eb0 const_(440 * pow(2, -54 / 12.0)) // 19.45
#define E0 const_(440 * pow(2, -53 / 12.0))  // 20.60
#define F0 const_(440 * pow(2, -52 / 12.0))  // 21.83
#define Fs0 const_(440 * pow(2, -51 / 12.0)) // 23.12
#define Gb0 const_(440 * pow(2, -51 / 12.0)) // 23.12
#define G0 const_(440 * pow(2, -50 / 12.0))  // 24.50
#define Gs0 const_(440 * pow(2, -49 / 12.0)) // 25.96
#define Ab0 const_(440 * pow(2, -49 / 12.0)) // 25.96
#define A0 const_(440 * pow(2, -48 / 12.0))  // 27.50
#define As0 const_(440 * pow(2, -47 / 12.0)) // 29.14
#define Bb0 const_(440 * pow(2, -47 / 12.0)) // 29.14
#define B0 const_(440 * pow(2, -46 / 12.0))  // 30.87
#define C1 const_(440 * pow(2, -45 / 12.0))  // 32.70
#define Cs1 const_(440 * pow(2, -44 / 12.0)) // 34.65
#define Db1 const_(440 * pow(2, -44 / 12.0)) // 34.65
#define D1 const_(440 * pow(2, -43 / 12.0))  // 36.71
#define Ds1 const_(440 * pow(2, -42 / 12.0)) // 38.89
#define Eb1 const_(440 * pow(2, -42 / 12.0)) // 38.89
#define E1 const_(440 * pow(2, -41 / 12.0))  // 41.20
#define F1 const_(440 * pow(2, -40 / 12.0))  // 43.65
#define Fs1 const_(440 * pow(2, -39 / 12.0)) // 46.25
#define Gb1 const_(440 * pow(2, -39 / 12.0)) // 46.25
#define G1 const_(440 * pow(2, -38 / 12.0))  // 49.00
#define Gs1 const_(440 * pow(2, -37 / 12.0)) // 51.91
#define Ab1 const_(440 * pow(2, -37 / 12.0)) // 51.91
#define A1 const_(440 * pow(2, -36 / 12.0))  // 55.00
#define As1 const_(440 * pow(2, -35 / 12.0)) // 58.27
#define Bb1 const_(440 * pow(2, -35 / 12.0)) // 58.27
#define B1 const_(440 * pow(2, -34 / 12.0))  // 61.74
#define C2 const_(440 * pow(2, -33 / 12.0))  // 65.41
#define Cs2 const_(440 * pow(2, -32 / 12.0)) // 69.30
#define Db2 const_(440 * pow(2, -32 / 12.0)) // 69.30
#define D2 const_(440 * pow(2, -31 / 12.0))  // 73.42
#define Ds2 const_(440 * pow(2, -30 / 12.0)) // 77.78
#define Eb2 const_(440 * pow(2, -30 / 12.0)) // 77.78
#define E2 const_(440 * pow(2, -29 / 12.0))  // 82.41
#define F2 const_(440 * pow(2, -28 / 12.0))  // 87.31
#define Fs2 const_(440 * pow(2, -27 / 12.0)) // 92.50
#define Gb2 const_(440 * pow(2, -27 / 12.0)) // 92.50
#define G2 const_(440 * pow(2, -26 / 12.0))  // 98.00
#define Gs2 const_(440 * pow(2, -25 / 12.0)) // 103.83
#define Ab2 const_(440 * pow(2, -25 / 12.0)) // 103.83
#define A2 const_(440 * pow(2, -24 / 12.0))  // 110.00
#define As2 const_(440 * pow(2, -23 / 12.0)) // 116.54
#define Bb2 const_(440 * pow(2, -23 / 12.0)) // 116.54
#define B2 const_(440 * pow(2, -22 / 12.0))  // 123.47
#define C3 const_(440 * pow(2, -21 / 12.0))  // 130.81
#define Cs3 const_(440 * pow(2, -20 / 12.0)) // 138.59
#define Db3 const_(440 * pow(2, -20 / 12.0)) // 138.59
#define D3 const_(440 * pow(2, -19 / 12.0))  // 146.83
#define Ds3 const_(440 * pow(2, -18 / 12.0)) // 155.56
#define Eb3 const_(440 * pow(2, -18 / 12.0)) // 155.56
#define E3 const_(440 * pow(2, -17 / 12.0))  // 164.81
#define F3 const_(440 * pow(2, -16 / 12.0))  // 174.61
#define Fs3 const_(440 * pow(2, -15 / 12.0)) // 185.00
#define Gb3 const_(440 * pow(2, -15 / 12.0)) // 185.00
#define G3 const_(440 * pow(2, -14 / 12.0))  // 196.00
#define Gs3 const_(440 * pow(2, -13 / 12.0)) // 207.65
#define Ab3 const_(440 * pow(2, -13 / 12.0)) // 207.65
#define A3 const_(440 * pow(2, -12 / 12.0))  // 220.00
#define As3 const_(440 * pow(2, -11 / 12.0)) // 233.08
#define Bb3 const_(440 * pow(2, -11 / 12.0)) // 233.08
#define B3 const_(440 * pow(2, -10 / 12.0))  // 246.94
#define C4 const_(440 * pow(2, -9 / 12.0))   // 261.63
#define Cs4 const_(440 * pow(2, -8 / 12.0))  // 277.18
#define Db4 const_(440 * pow(2, -8 / 12.0))  // 277.18
#define D4 const_(440 * pow(2, -7 / 12.0))   // 293.66
#define Ds4 const_(440 * pow(2, -6 / 12.0))  // 311.13
#define Eb4 const_(440 * pow(2, -6 / 12.0))  // 311.13
#define E4 const_(440 * pow(2, -5 / 12.0))   // 329.63
#define F4 const_(440 * pow(2, -4 / 12.0))   // 349.23
#define Fs4 const_(440 * pow(2, -3 / 12.0))  // 369.99
#define Gb4 const_(440 * pow(2, -3 / 12.0))  // 369.99
#define G4 const_(440 * pow(2, -2 / 12.0))   // 392.00
#define Gs4 const_(440 * pow(2, -1 / 12.0))  // 415.30
#define Ab4 const_(440 * pow(2, -1 / 12.0))  // 415.30
#define A4 const_(440 * pow(2, 0 / 12.0))    // 440.00
#define As4 const_(440 * pow(2, 1 / 12.0))   // 466.16
#define Bb4 const_(440 * pow(2, 1 / 12.0))   // 466.16
#define B4 const_(440 * pow(2, 2 / 12.0))    // 493.88
#define C5 const_(440 * pow(2, 3 / 12.0))    // 523.25
#define Cs5 const_(440 * pow(2, 4 / 12.0))   // 554.37
#define Db5 const_(440 * pow(2, 4 / 12.0))   // 554.37
#define D5 const_(440 * pow(2, 5 / 12.0))    // 587.33
#define Ds5 const_(440 * pow(2, 6 / 12.0))   // 622.25
#define Eb5 const_(440 * pow(2, 6 / 12.0))   // 622.25
#define E5 const_(440 * pow(2, 7 / 12.0))    // 659.26
#define F5 const_(440 * pow(2, 8 / 12.0))    // 698.46
#define Fs5 const_(440 * pow(2, 9 / 12.0))   // 739.99
#define Gb5 const_(440 * pow(2, 9 / 12.0))   // 739.99
#define G5 const_(440 * pow(2, 10 / 12.0))   // 783.99
#define Gs5 const_(440 * pow(2, 11 / 12.0))  // 830.61
#define Ab5 const_(440 * pow(2, 11 / 12.0))  // 830.61
#define A5 const_(440 * pow(2, 12 / 12.0))   // 880.00
#define As5 const_(440 * pow(2, 13 / 12.0))  // 932.33
#define Bb5 const_(440 * pow(2, 13 / 12.0))  // 932.33
#define B5 const_(440 * pow(2, 14 / 12.0))   // 987.77
#define C6 const_(440 * pow(2, 15 / 12.0))   // 1046.50
#define Cs6 const_(440 * pow(2, 16 / 12.0))  // 1108.73
#define Db6 const_(440 * pow(2, 16 / 12.0))  // 1108.73
#define D6 const_(440 * pow(2, 17 / 12.0))   // 1174.66
#define Ds6 const_(440 * pow(2, 18 / 12.0))  // 1244.51
#define Eb6 const_(440 * pow(2, 18 / 12.0))  // 1244.51
#define E6 const_(440 * pow(2, 19 / 12.0))   // 1318.51
#define F6 const_(440 * pow(2, 20 / 12.0))   // 1396.91
#define Fs6 const_(440 * pow(2, 21 / 12.0))  // 1479.98
#define Gb6 const_(440 * pow(2, 21 / 12.0))  // 1479.98
#define G6 const_(440 * pow(2, 22 / 12.0))   // 1567.98
#define Gs6 const_(440 * pow(2, 23 / 12.0))  // 1661.22
#define Ab6 const_(440 * pow(2, 23 / 12.0))  // 1661.22
#define A6 const_(440 * pow(2, 24 / 12.0))   // 1760.00
#define As6 const_(440 * pow(2, 25 / 12.0))  // 1864.66
#define Bb6 const_(440 * pow(2, 25 / 12.0))  // 1864.66
#define B6 const_(440 * pow(2, 26 / 12.0))   // 1975.53
#define C7 const_(440 * pow(2, 27 / 12.0))   // 2093.00
#define Cs7 const_(440 * pow(2, 28 / 12.0))  // 2217.46
#define Db7 const_(440 * pow(2, 28 / 12.0))  // 2217.46
#define D7 const_(440 * pow(2, 29 / 12.0))   // 2349.32
#define Ds7 const_(440 * pow(2, 30 / 12.0))  // 2489.02
#define Eb7 const_(440 * pow(2, 30 / 12.0))  // 2489.02
#define E7 const_(440 * pow(2, 31 / 12.0))   // 2637.02
#define F7 const_(440 * pow(2, 32 / 12.0))   // 2793.83
#define Fs7 const_(440 * pow(2, 33 / 12.0))  // 2959.96
#define Gb7 const_(440 * pow(2, 33 / 12.0))  // 2959.96
#define G7 const_(440 * pow(2, 34 / 12.0))   // 3135.96
#define Gs7 const_(440 * pow(2, 35 / 12.0))  // 3322.44
#define Ab7 const_(440 * pow(2, 35 / 12.0))  // 3322.44
#define A7 const_(440 * pow(2, 36 / 12.0))   // 3520.00
#define As7 const_(440 * pow(2, 37 / 12.0))  // 3729.31
#define Bb7 const_(440 * pow(2, 37 / 12.0))  // 3729.31
#define B7 const_(440 * pow(2, 38 / 12.0))   // 3951.07
#define C8 const_(440 * pow(2, 39 / 12.0))   // 4186.01
#define Cs8 const_(440 * pow(2, 40 / 12.0))  // 4434.92
#define Db8 const_(440 * pow(2, 40 / 12.0))  // 4434.92
#define D8 const_(440 * pow(2, 41 / 12.0))   // 4698.64
#define Ds8 const_(440 * pow(2, 42 / 12.0))  // 4978.03
#define Eb8 const_(440 * pow(2, 42 / 12.0))  // 4978.03
#define E8 const_(440 * pow(2, 43 / 12.0))   // 5274.04
#define F8 const_(440 * pow(2, 44 / 12.0))   // 5587.65
#define Fs8 const_(440 * pow(2, 45 / 12.0))  // 5919.91
#define Gb8 const_(440 * pow(2, 45 / 12.0))  // 5919.91
#define G8 const_(440 * pow(2, 46 / 12.0))   // 6271.93
#define Gs8 const_(440 * pow(2, 47 / 12.0))  // 6644.88
#define Ab8 const_(440 * pow(2, 47 / 12.0))  // 6644.88
#define A8 const_(440 * pow(2, 48 / 12.0))   // 7040.00
#define As8 const_(440 * pow(2, 49 / 12.0))  // 7458.62
#define Bb8 const_(440 * pow(2, 49 / 12.0))  // 7458.62
#define B8 const_(440 * pow(2, 50 / 12.0))   // 7902.13
#define C9 const_(440 * pow(2, 51 / 12.0))   // 8372.02
#define Cs9 const_(440 * pow(2, 52 / 12.0))  // 8869.84
#define Db9 const_(440 * pow(2, 52 / 12.0))  // 8869.84
#define D9 const_(440 * pow(2, 53 / 12.0))   // 9397.27
#define Ds9 const_(440 * pow(2, 54 / 12.0))  // 9956.06
#define Eb9 const_(440 * pow(2, 54 / 12.0))  // 9956.06
#define E9 const_(440 * pow(2, 55 / 12.0))   // 10548.08
#define F9 const_(440 * pow(2, 56 / 12.0))   // 11175.30
#define Fs9 const_(440 * pow(2, 57 / 12.0))  // 11839.82
#define Gb9 const_(440 * pow(2, 57 / 12.0))  // 11839.82
#define G9 const_(440 * pow(2, 58 / 12.0))   // 12543.85
#define Gs9 const_(440 * pow(2, 59 / 12.0))  // 13289.75
#define Ab9 const_(440 * pow(2, 59 / 12.0))  // 13289.75
#define A9 const_(440 * pow(2, 60 / 12.0))   // 14080.00
#define As9 const_(440 * pow(2, 61 / 12.0))  // 14917.24
#define Bb9 const_(440 * pow(2, 61 / 12.0))  // 14917.24
#define B9 const_(440 * pow(2, 62 / 12.0))   // 15804.27
#define C10 const_(440 * pow(2, 63 / 12.0))  // 16744.04
#define Cs10 const_(440 * pow(2, 64 / 12.0)) // 17739.69
#define Db10 const_(440 * pow(2, 64 / 12.0)) // 17739.69
#define D10 const_(440 * pow(2, 65 / 12.0))  // 18794.55
#define Ds10 const_(440 * pow(2, 66 / 12.0)) // 19912.13
#define Eb10 const_(440 * pow(2, 66 / 12.0)) // 19912.13
#define E10 const_(440 * pow(2, 67 / 12.0))  // 21096.16
#define F10 const_(440 * pow(2, 68 / 12.0))  // 22350.61
#define Fs10 const_(440 * pow(2, 69 / 12.0)) // 23679.64
#define Gb10 const_(440 * pow(2, 69 / 12.0)) // 23679.64
#define G10 const_(440 * pow(2, 70 / 12.0))  // 25087.71
#define Gs10 const_(440 * pow(2, 71 / 12.0)) // 26579.50
#define Ab10 const_(440 * pow(2, 71 / 12.0)) // 26579.50
#define A10 const_(440 * pow(2, 72 / 12.0))  // 28160.00
#define As10 const_(440 * pow(2, 73 / 12.0)) // 29834.48
#define Bb10 const_(440 * pow(2, 73 / 12.0)) // 29834.48
#define B10 const_(440 * pow(2, 74 / 12.0))  // 31608.53

static const char *note_names[] = {"C", "Cs", "Db", "D", "Ds", "Eb", "E", "F", "Fs", "Gb", "G", "Gs", "Ab", "A", "As", "Bb", "B"};

void print_notes_h()
{
    for (int i = 0; i < 17 * 11; i++)
    {
        const char *note = note_names[i % 17];
        int octave = i / 17;
        int index = round((i + 4) * 12.0 / 17 - 59.95);
        double freq = 440 * pow(2, index / 12.0);
        fprintf(stderr, "#define %s%d const_(440 * pow(2, %d / 12.0)) // %.2f\n", note, octave, index, freq);
    }
}

void test_notes()
{
    double epsilon = 1e-4;
    assert(fabs(gen_eval(gen_create(G10, .1)) - 25087.707903) < epsilon);
}

#endif // CSYNTH_NOTES_H
