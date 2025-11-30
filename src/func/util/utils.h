#ifndef CSYNTH_UTILS_H
#define CSYNTH_UTILS_H

#include "../gen/param.h"
#include "../op/inv.h"
#include "../util/times.h"
#include "./dump.h"
#include "./fps.h"
#include "./gauge.h"
#include "./gram.h"
#include "./mem.h"
#include "./print.h"
#include "./record.h"
#include "./scope.h"
#include "./wrap.h"

/** @brief Shorthand for `gauge_create`, including a display label. */
Func *gauge(const char *label, Func *input)
{
    display_label(label);
    return gauge_create(label, param_create(EvalParamDisplayTick), input);
}

/** @brief Shorthand for `wrap_create`. */
Func *wrap(wrap_callback callback, Func *input, void *context) { return wrap_create(callback, input, context); }
/** @brief Shorthand for `wrap_create`, using an EvalParamPitchTick timer. */
Func *wrap_(wrap_callback callback, void *context) { return wrap(callback, timer(EvalParamPitchTick), context); }

#define record_channels(_filename, _sample_rate, ...) (record_filename(_filename, _sample_rate, ARGS_FUNC(__VA_ARGS__)))
/** @brief Shorthand for `record_create`, using SAMPLE_RATE and a mono channel.
 * */
Func *record(const char *filename, Func *input) { return record_channels(filename, SAMPLE_RATE, input); }
/** @brief Shorthand for `record_create`, using SAMPLE_RATE and
 * DEFAULT_WAV_FILENAME.*/
Func *record_(Func *input) { return record(DEFAULT_WAV_FILENAME, input); }
/** @brief Shorthand for `record_create`, using SAMPLE_RATE and two stereo
 * channels. */
Func *record_stereo(const char *filename, Func *left, Func *right) { return record_channels(filename, SAMPLE_RATE, left, right); }
/** @brief Shorthand for `record_create`, using SAMPLE_RATE and two stereo
 * channels with DEFAULT_WAV_FILENAME. */
Func *record_stereo_(Func *left, Func *right) { return record_stereo(DEFAULT_WAV_FILENAME, left, right); }

/** @brief Shorthand for `dump_create` for 20 samples. */
Func *log20(Func *input) { return dump_create(20, 1, input); }
/** @brief Shorthand for `dump_create` for 1000 samples. */
Func *log1k(Func *input) { return dump_create(1000, 1, input); }
/** @brief Shorthand for `dump_create` for 10 samples every 100ms. */
Func *log10sec(Func *input) { return dump_create(10, 4410, input); }

/** @brief Shorthand for `print_create`. */
Func *print(const char *text, Func *input) { return print_create(text, input); }

/** @brief Shorthand for `fps_create`, including a display label. */
Func *fps(const char *label, Func *input)
{
    display_label(label);
    return fps_create(label, input);
}

/** @brief Shorthand for `mem_create`, including an alloc and free label. */
Func *mem(Func *input)
{
    display_label("alloc");
    display_label("free");
    return mem_create(input);
}

/** @brief Plot oscilloscope. */
Func *scope(Func *frequency, RenderPipe *pipe, Func *input)
{
    return scope_create(mul(param(EvalParamPitchTick), frequency), 10, 10, 1.0, pipe, input);
}

/** @brief Plot spectrogram. */
Func *gram(Func *input, RenderPipe *pipe)
{
    return gram_create(input, pipe);
}

#endif // CSYNTH_UTILS_H
