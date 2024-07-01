//
// utils.h - Utils
//
#ifndef CSYNTH_UTILS_H
#define CSYNTH_UTILS_H

#include "../op/inv.h"
#include "../time/times.h"
#include "./gauge.h"
#include "./logger.h"
#include "./print.h"
#include "./record.h"
#include "./wrap.h"

Func *gauge(const char *label, Func *input)
{
    display_label(label);
    return gauge_create(label, ticker_(EvalTickDisplay, 1), input);
}

Func *wrap(wrap_callback callback, Func *input, void *context) { return wrap_create(callback, input, context); }
Func *wrap_(wrap_callback callback, void *context) { return wrap(callback, pitch_timer_(1), context); }

#define record_channels(_filename, _sample_rate, ...) (record_create(_filename, _sample_rate, FUNCS(__VA_ARGS__)))
Func *record(const char *filename, Func *input) { return record_channels(filename, DEFAULT_SAMPLE_RATE, input); }
Func *record_(Func *input) { return record(DEFAULT_WAV_FILENAME, input); }
Func *record_stereo(const char *filename, Func *left, Func *right) { return record_channels(filename, DEFAULT_SAMPLE_RATE, left, right); }
Func *record_stereo_(Func *left, Func *right) { return record_stereo(DEFAULT_WAV_FILENAME, left, right); }

Func *log20(Func *input) { return logger_create(20, 1, input); }
Func *log1k(Func *input) { return logger_create(1000, 1, input); }
Func *log10sec(Func *input) { return logger_create(10, 4410, input); }

Func *print(const char *text, Func *input) { return print_create(text, input); }

#endif // CSYNTH_UTILS_H
