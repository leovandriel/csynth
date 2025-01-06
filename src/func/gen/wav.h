#ifndef CSYNTH_WAV_H
#define CSYNTH_WAV_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../io/reader.h"

/** @see wav_create */
typedef struct
{
    /** @brief Sample data loaded in memory. */
    PcmBuffer buffer;
    /** @brief Channel to read samples from. */
    int channel;
    /** @brief Time offset to read next sample at. */
    double time;
} WavContext;

static double wav_eval(__U size_t count, Gen **args, Eval *eval, void *context_)
{
    WavContext *context = (WavContext *)context_;
    sample_t sample = reader_sample(&context->buffer, context->time, context->channel);
    double output = (double)sample / 32767;
    double tick = gen_eval(args[0], eval);
    context->time += tick;
    return output;
}

static void wav_cleanup(void *initial_)
{
    WavContext *initial = (WavContext *)initial_;
    reader_free(&initial->buffer);
}

/**
 * @brief Create a function that reads samples from a WAV file.
 *
 * This function creates a generator that plays back PCM audio data from a WAV file.
 * The samples are read from the specified channel at a rate controlled by the tick
 * parameter. The output values are normalized to the range [-1, 1] by dividing
 * the 16-bit integer samples by 32767.
 *
 * The reading position advances by the tick amount each sample. For normal playback
 * at the original sample rate, tick should be 1.0. Values less than 1 will play
 * slower (pitch down), values greater than 1 will play faster (pitch up). Negative
 * values will play backwards.
 *
 * @param buffer PcmBuffer struct containing the WAV file samples loaded in memory.
 * @param free If true, the buffer will be automatically freed when the function is
 *            destroyed. If false, the caller retains ownership of the buffer.
 * @param channel Zero-based index of the channel to read from. Must be less than
 *               the number of channels in the WAV file.
 * @param tick Function that controls the reading speed in samples per sample.
 *            Speed multiplier = tick * output_rate / input_rate
 * @return Func* WAV playback function that outputs normalized samples in [-1, 1].
 */
Func *wav_create(PcmBuffer buffer, bool free, int channel, Func *tick)
{
    WavContext initial = {
        .buffer = buffer,
        .channel = channel,
    };
    return func_create(NULL, wav_eval, NULL, free ? wav_cleanup : NULL, sizeof(WavContext), &initial, FuncFlagNone, tick);
}

/**
 * @brief Create a function that reads samples from a WAV file.
 *
 * @param file File handle of the WAV file.
 * @param channel Channel to read from.
 * @param input Function that controls the reading speed.
 * @return Func* WAV function
 */
Func *wav_file(FILE *file, int channel, Func *input)
{
    PcmBuffer buffer = {0};
    if (reader_read_file(&buffer, file) != csErrorNone)
    {
        return NULL;
    }
    return wav_create(buffer, true, channel, input);
}

/**
 * @brief Create a function that reads samples from a WAV file.
 *
 * @param filename Filename of the WAV file.
 * @param channel Channel to read from.
 * @param input Function that controls the reading speed.
 * @return Func* WAV function
 */
Func *wav_filename(const char *filename, int channel, Func *input)
{
    PcmBuffer buffer = {0};
    if (reader_read_filename(&buffer, filename) != csErrorNone)
    {
        return NULL;
    }
    return wav_create(buffer, true, channel, input);
}

#endif // CSYNTH_WAV_H
