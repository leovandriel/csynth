//usr/bin/gcc "$0" -o bin/inspect_wav -Wall -Wextra -O3 -lm -lportaudio && ./bin/inspect_wav "$@"; exit $?

// To convert MP3 to WAV: ffmpeg -i in.mp3 -fflags bitexact out.wav

#include <portaudio.h>
#include <stdio.h>
#include <string.h>

#include "../src/io/reader.h"
#include "../src/io/wav_header.h"
#include "../src/io/writer.h"
#include "../src/util/fourier.h"
#include "../src/io/ppm_header.h"

/**
 * @brief Format an integer with commas.
 *
 * @param n Integer to format.
 * @param buffer Buffer to store the formatted string.
 * @return char* Pointer to the formatted string.
 */
char *fint(long long n, char *buffer)
{
    char tmp[32];
    sprintf(tmp, "%lld", n);

    int len = strlen(tmp);
    int outlen = len + (len - 1) / 3;
    buffer[outlen] = '\0';

    int in = len - 1;
    int count = 0;

    for (int i = outlen - 1; i >= 0; i--)
    {
        buffer[i] = tmp[in--];
        if (++count == 3 && in >= 0)
        {
            buffer[--i] = ',';
            count = 0;
        }
    }
    return buffer;
}

csError info(const char *filename)
{
    WavHeader header = {0};
    csError error = wav_header_read_filename(&header, filename);
    if (error != csErrorNone)
    {
        return error;
    }
    char buffer[64];
    printf("Filename   : %s\n", filename);
    printf("Samples    : %s\n", fint(8 * header.data_size / header.num_channels / header.bits_sample, buffer));
    printf("Seconds    : %.3f\n", 1.0 * header.data_size / header.byte_rate);
    printf("Riff type  : %.4s\n", header.riff_type);
    printf("File size  : %s\n", fint(header.file_size, buffer));
    printf("File type  : %.4s\n", header.file_type);
    printf("Format mark: %.4s\n", header.format_mark);
    printf("Format size: %s\n", fint(header.format_size, buffer));
    printf("Format type: %s\n", fint(header.format_type, buffer));
    printf("Channels   : %s\n", fint(header.num_channels, buffer));
    printf("Sample rate: %s\n", fint(header.sample_rate, buffer));
    printf("Byte rate  : %s\n", fint(header.byte_rate, buffer));
    printf("Block align: %s\n", fint(header.block_align, buffer));
    printf("Sample bits: %s\n", fint(header.bits_sample, buffer));
    printf("Data chunk : %.4s\n", header.data_chunk);
    printf("Data size  : %s\n", fint(header.data_size, buffer));
    return csErrorNone;
}

typedef struct
{
    PcmBuffer buffer;
    size_t offset;
} PlayData;

static int play_callback(__U const void *input, void *output_, size_t count, __U const PaStreamCallbackTimeInfo *info, __U PaStreamCallbackFlags flags, void *data_)
{
    PlayData *data = (PlayData *)data_;
    int16_t *output = (int16_t *)output_;
    for (size_t frame = 0; frame < count; frame++)
    {
        for (size_t index = 0; index < data->buffer.channel_count; index++)
        {
            *(output++) = data->buffer.samples[data->offset];
            data->offset++;
            if (data->offset >= data->buffer.sample_count * data->buffer.channel_count)
            {
                data->offset = 0;
            }
        }
    }
    return paContinue;
}

/**
 * @brief Play a WAV file with PortAudio.
 *
 * @param filename Path to the WAV file to play.
 * @return csError Error code, zero on success.
 */
csError play(const char *filename)
{
    PlayData data = {0};
    csError error = reader_read_filename(&data.buffer, filename);
    if (error != csErrorNone)
    {
        return error;
    }
    PaError pa_error = Pa_Initialize();
    if (pa_error != paNoError)
    {
        reader_free(&data.buffer);
        return error_type_message(csErrorPortAudio, "Unable to initialize: %s", Pa_GetErrorText(pa_error), pa_error);
    }
    PaStream *stream = NULL;
    pa_error = Pa_OpenDefaultStream(&stream, 0, (int)data.buffer.channel_count, paInt16, (int)data.buffer.sample_rate, 256, play_callback, &data);
    if (pa_error != paNoError)
    {
        Pa_Terminate();
        reader_free(&data.buffer);
        return error_type_message(csErrorPortAudio, "Unable to open stream: %s", Pa_GetErrorText(pa_error), pa_error);
    }
    pa_error = Pa_StartStream(stream);
    if (pa_error != paNoError)
    {
        Pa_CloseStream(stream);
        Pa_Terminate();
        reader_free(&data.buffer);
        return error_type_message(csErrorPortAudio, "Unable to start stream: %s", Pa_GetErrorText(pa_error), pa_error);
    }
    getchar();
    if (pa_error != paNoError)
    {
        Pa_Terminate();
        reader_free(&data.buffer);
        return error_type_message(csErrorPortAudio, "Unable to close stream: %s", Pa_GetErrorText(pa_error), pa_error);
    }
    pa_error = Pa_Terminate();
    if (pa_error != paNoError)
    {
        reader_free(&data.buffer);
        return error_type_message(csErrorPortAudio, "Unable to terminate: %s", Pa_GetErrorText(pa_error), pa_error);
    }
    reader_free(&data.buffer);
    return csErrorNone;
}

/**
 * @brief Cut a WAV file.
 *
 * @param start Start sample index.
 * @param end End sample index (exclusive).
 * @param in_filename Input filename.
 * @param out_filename Output filename.
 * @return csError Error code, zero on success.
 */
csError cut(size_t start, size_t end, const char *in_filename, const char *out_filename)
{
    PcmBuffer buffer = {0};
    csError error = reader_read_filename(&buffer, in_filename);
    if (error != csErrorNone)
    {
        return error;
    }
    if (end > buffer.sample_count)
    {
        end = buffer.sample_count;
    }
    if (start > end)
    {
        return error_type_message(csErrorInvalidArgument, "Start is greater than end");
    }
    size_t sample_count = end - start;
    PcmBuffer out_buffer = {0};
    out_buffer.sample_count = sample_count;
    out_buffer.channel_count = buffer.channel_count;
    out_buffer.sample_rate = buffer.sample_rate;
    out_buffer.samples = (sample_t *)malloc_(sample_count * buffer.channel_count * sizeof(sample_t));
    if (out_buffer.samples == NULL)
    {
        return error_type(csErrorMemoryAlloc);
    }
    for (size_t i = 0; i < sample_count; i++)
    {
        for (size_t j = 0; j < buffer.channel_count; j++)
        {
            out_buffer.samples[i * buffer.channel_count + j] = buffer.samples[(start + i) * buffer.channel_count + j];
        }
    }
    reader_free(&buffer);
    error = writer_write_filename(&out_buffer, out_filename);
    if (error != csErrorNone)
    {
        return error;
    }
    reader_free(&out_buffer);
    return csErrorNone;
}

csError gram(size_t window_size, size_t step_size, const char *in_filename, const char *out_filename)
{
    if (!fourier_is_power_of_two(window_size))
    {
        return error_type_message(csErrorInvalidArgument, "Window size must be a power of 2, got %zu", window_size);
    }
    PcmBuffer buffer = {0};
    csError error = reader_read_filename(&buffer, in_filename);
    if (error != csErrorNone)
    {
        return error;
    }
    size_t width = buffer.sample_count / step_size;
    size_t height = window_size / 2;
    uint32_t *image_buffer = (uint32_t *)malloc_(width * height * sizeof(uint32_t));
    if (image_buffer == NULL)
    {
        reader_free(&buffer);
        return error_type(csErrorMemoryAlloc);
    }
    double *in_buffer = (double *)malloc_(window_size * sizeof(double));
    if (in_buffer == NULL)
    {
        free_(image_buffer);
        reader_free(&buffer);
        return error_type(csErrorMemoryAlloc);
    }
    double *out_buffer = (double *)malloc_(height * sizeof(double));
    if (out_buffer == NULL)
    {
        free_(in_buffer);
        free_(image_buffer);
        reader_free(&buffer);
        return error_type(csErrorMemoryAlloc);
    }
    size_t sample_offset = 0, frame_offset = 0;
    for (size_t i = 0; i < buffer.sample_count; i++)
    {
        in_buffer[sample_offset % window_size] = (double)buffer.samples[i * buffer.channel_count] / (double)0x8000;
        sample_offset++;
        if (sample_offset % step_size == 0) {
            fourier_transform(in_buffer, window_size, sample_offset, out_buffer);
            for (size_t j = 0; j < height; j++)
            {
                image_buffer[j * width + frame_offset] = fourier_value_to_color(out_buffer[height - j - 1]);
            }
            frame_offset++;
        }
    }
    ppm_bgra_to_rgb((unsigned char *)image_buffer, width, height);
    ppm_write_filename(out_filename, width, height, (unsigned char *)image_buffer);
    free_(out_buffer);
    free_(in_buffer);
    free_(image_buffer);
    reader_free(&buffer);
    return csErrorNone;
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s tool ..\n", argv[0]);
        return -1;
    }
    const char *tool = argv[1];
    if (strcmp(tool, "info") == 0)
    {
        if (argc < 3)
        {
            fprintf(stderr, "Usage: %s info filename\n", argv[0]);
            return -1;
        }
        const char *filename = argv[2];
        return info(filename);
    }

    if (strcmp(tool, "play") == 0)
    {
        if (argc < 3)
        {
            fprintf(stderr, "Usage: %s play filename\n", argv[0]);
            return -1;
        }
        const char *filename = argv[2];
        return play(filename);
    }

    if (strcmp(tool, "cut") == 0)
    {
        if (argc < 6)
        {
            fprintf(stderr, "Usage: %s cut start end in-filename out-filename\n", argv[0]);
            return -1;
        }
        size_t start = (size_t)atoll(argv[2]);
        size_t end = (size_t)atoll(argv[3]);
        const char *in_filename = argv[4];
        const char *out_filename = argv[5];
        return cut(start, end, in_filename, out_filename);
    }

    if (strcmp(tool, "gram") == 0)
    {
        if (argc < 6)
        {
            fprintf(stderr, "Usage: %s gram window-size step-size in-filename out-filename\n", argv[0]);
            return -1;
        }
        size_t window_size = (size_t)atoll(argv[2]);
        size_t step_size = (size_t)atoll(argv[3]);
        const char *in_filename = argv[4];
        const char *out_filename = argv[5];
        return gram(window_size, step_size, in_filename, out_filename);
    }

    return error_type_message(csErrorInvalidArgument, "Unknown tool: %s", tool);
}