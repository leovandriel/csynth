//usr/bin/gcc "$0" -o bin/inspect_wav -Wall -Wextra -O3 -lm -lportaudio && ./bin/inspect_wav "$@"; exit $?

// To convert MP3 to WAV: ffmpeg -i in.mp3 -fflags bitexact out.wav

#include <portaudio.h>
#include <stdio.h>
#include <string.h>

#include "../src/io/ppm_header.h"
#include "../src/io/reader.h"
#include "../src/io/wav_header.h"
#include "../src/io/writer.h"
#include "../src/util/fourier.h"
#include "../src/util/note.h"
#include "../src/util/sort.h"

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
    pa_error = Pa_StopStream(stream);
    if (pa_error != paNoError)
    {
        Pa_CloseStream(stream);
        Pa_Terminate();
        reader_free(&data.buffer);
        return error_type_message(csErrorPortAudio, "Unable to stop stream: %s", Pa_GetErrorText(pa_error), pa_error);
    }
    pa_error = Pa_CloseStream(stream);
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
csError cut(size_t start, size_t length, const char *in_filename, const char *out_filename)
{
    PcmBuffer buffer = {0};
    csError error = reader_read_filename(&buffer, in_filename);
    if (error != csErrorNone)
    {
        return error;
    }
    size_t end = start + length;
    if (end > buffer.sample_count)
    {
        end = buffer.sample_count;
    }
    if (start > end)
    {
        reader_free(&buffer);
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
        reader_free(&buffer);
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
        reader_free(&out_buffer);
        return error;
    }
    reader_free(&out_buffer);
    return csErrorNone;
}

csError gram(size_t window_exp, double step_seconds, const char *in_filename, const char *out_filename, size_t channel)
{
    PcmBuffer buffer = {0};
    csError error = reader_read_filename(&buffer, in_filename);
    if (error != csErrorNone)
    {
        return error;
    }
    size_t step_size = (size_t)(step_seconds * buffer.sample_rate);
    size_t width = buffer.sample_count / step_size;
    size_t window_size = 1 << window_exp;
    size_t height = window_size / 2;
    uint32_t *image_buffer = (uint32_t *)calloc_(width * height, sizeof(uint32_t));
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
        in_buffer[sample_offset % window_size] = (double)buffer.samples[i * buffer.channel_count + channel] / (double)0x8000;
        sample_offset++;
        if (sample_offset % step_size == 0)
        {
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
    printf("Bin size: %.3f Hz\n", (double)buffer.sample_rate / (double)window_size);
    free_(out_buffer);
    free_(in_buffer);
    free_(image_buffer);
    reader_free(&buffer);
    return csErrorNone;
}

csError fft(size_t start, size_t window_exp, const char *in_filename, const char *out_filename, size_t channel, size_t height, double db_range)
{
    PcmBuffer buffer = {0};
    csError error = reader_read_filename(&buffer, in_filename);
    if (error != csErrorNone)
    {
        return error;
    }
    size_t window_size = 1 << window_exp;
    size_t width = window_size / 2;
    uint32_t *image_buffer = (uint32_t *)calloc_(width * height, sizeof(uint32_t));
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
    for (size_t j = 1; j < db_range / 20; j += 1)
    {
        size_t scaled = (size_t)math_clamp((-20.0 * j + db_range) / db_range * height, 0.0, height - 1);
        for (size_t i = 0; i < width; i++)
        {
            image_buffer[(height - scaled - 1) * width + i] = ((const int[]){0xFF300000, 0xFF002000, 0xFF000050})[j % 3];
        }
    }
    for (size_t i = 0; i < window_size; i++)
    {
        in_buffer[i] = (double)buffer.samples[((start + i) * buffer.channel_count + channel) % (buffer.sample_count * buffer.channel_count)] / (double)0x8000;
    }
    fourier_transform(in_buffer, window_size, 0, in_buffer);
    for (size_t j = 0; j < width; j++)
    {
        double db = fourier_value_to_db(in_buffer[j]);
        size_t scaled = (size_t)math_clamp((db + db_range) / db_range * height, 0.0, height - 1);
        image_buffer[(height - scaled - 1) * width + j] = 0xFFFFFFFF;
    }
    ppm_bgra_to_rgb((unsigned char *)image_buffer, width, height);
    ppm_write_filename(out_filename, width, height, (unsigned char *)image_buffer);
    printf("Bin size: %.3f Hz\n", (double)buffer.sample_rate / (double)window_size);
    free_(in_buffer);
    free_(image_buffer);
    reader_free(&buffer);
    return csErrorNone;
}

csError scope(size_t start, double frequency, size_t periods, const char *in_filename, const char *out_filename, size_t channel, size_t height)
{
    PcmBuffer buffer = {0};
    csError error = reader_read_filename(&buffer, in_filename);
    if (error != csErrorNone)
    {
        return error;
    }
    size_t width = (size_t)(buffer.sample_rate / frequency);
    uint32_t *image_buffer = (uint32_t *)calloc_(width * height, sizeof(uint32_t));
    if (image_buffer == NULL)
    {
        reader_free(&buffer);
        return error_type(csErrorMemoryAlloc);
    }
    for (size_t i = 0; i < width; i++)
    {
        image_buffer[(height / 2) * width + i] = 0xFF222222;
    }
    for (size_t i = 0; i < width * periods; i++)
    {
        double amplitude = (double)buffer.samples[((start + i) * buffer.channel_count + channel) % (buffer.sample_count * buffer.channel_count)] / (double)0x8000;
        size_t y = (size_t)math_clamp(height * (amplitude + 1.0) / 2.0, 0.0, height - 1);
        size_t color = (size_t)math_clamp((double)0x100 * (double)i / (double)width / (double)periods, 0.0, 0xFF);
        image_buffer[y * width + i % width] = 0xFF000000 + (color << 16) + (color << 8) + color;
    }
    printf("Period: %zu samples\n", width);
    ppm_bgra_to_rgb((unsigned char *)image_buffer, width, height);
    ppm_write_filename(out_filename, width, height, (unsigned char *)image_buffer);
    free_(image_buffer);
    reader_free(&buffer);
    return csErrorNone;
}

static int freq_compare(const void *a, const void *b, const void *context)
{
    double *in_buffer = (double *)context;
    double a_value = in_buffer[*(size_t *)a];
    double b_value = in_buffer[*(size_t *)b];
    return a_value < b_value ? 1 : (a_value > b_value ? -1 : 0);
}

csError peaks(size_t start, size_t window_exp, const char *filename, size_t channel, size_t count)
{
    PcmBuffer buffer = {0};
    csError error = reader_read_filename(&buffer, filename);
    if (error != csErrorNone)
    {
        return error;
    }
    size_t window_size = 1 << window_exp;
    double *in_buffer = (double *)malloc_(window_size * sizeof(double));
    if (in_buffer == NULL)
    {
        reader_free(&buffer);
        return error_type(csErrorMemoryAlloc);
    }
    size_t *sort_buffer = (size_t *)malloc_(window_size / 2 * sizeof(size_t));
    if (sort_buffer == NULL)
    {
        free_(in_buffer);
        reader_free(&buffer);
        return error_type(csErrorMemoryAlloc);
    }
    for (size_t i = 0; i < window_size; i++)
    {
        in_buffer[i] = (double)buffer.samples[((start + i) * buffer.channel_count + channel) % (buffer.sample_count * buffer.channel_count)] / (double)0x8000;
    }
    fourier_transform(in_buffer, window_size, 0, in_buffer);
    for (size_t i = 0; i < window_size / 2; i++)
    {
        sort_buffer[i] = i;
    }
    sort(sort_buffer, window_size / 2, sizeof(size_t), freq_compare, in_buffer);
    double bin_size = (double)buffer.sample_rate / (double)window_size;
    double dominant_freq = -1.0, dominant_db = -1.0;
    size_t found = 0;
    for (size_t i = 0; i < window_size / 2; i++)
    {
        size_t index = sort_buffer[i];
        // ignore DC and Nyquist frequencies
        if (index == 0 || index == window_size / 2 - 1)
        {
            continue;
        }
        // skip is near previous bin
        bool is_near = false;
        for (size_t j = 0; j < i; j++)
        {
            size_t diff = index > sort_buffer[j] ? index - sort_buffer[j] : sort_buffer[j] - index;
            if (diff <= 1)
            {
                is_near = true;
                break;
            }
        }
        if (is_near)
        {
            continue;
        }
        double frequency = (double)index * bin_size;
        double db = fourier_value_to_db(in_buffer[index]);
        double a = fourier_value_to_db(in_buffer[index - 1]);
        double b = fourier_value_to_db(in_buffer[index + 1]);
        if (db < a || db < b)
        {
            continue;
        }
        // interpolate for higher precision
        double denom = a + b - 2.0 * db;
        if (denom != 0.0)
        {
            double delta = 0.5 * (a - b) / denom;
            frequency += delta * bin_size;
            db -= 0.25 * (a - b) * delta;
        }
        if (found == 0)
        {
            dominant_freq = frequency;
            dominant_db = db;
        }
        double note_index = note_frequency_to_index(frequency);
        double note_index_frac = note_index - round(note_index);
        char note[4];
        note_index_to_string(note_index, note, 4);
        printf("%.2f Hz (%s%.2f), %.2f dB (%s%.2f), %s%s%.0f%%\n",
               frequency,
               frequency >= dominant_freq ? "x" : "/",
               frequency >= dominant_freq ? frequency / dominant_freq : dominant_freq / frequency,
               db,
               db > dominant_db ? "+" : "-",
               db > dominant_db ? db - dominant_db : dominant_db - db,
               note,
               note_index_frac > 0.0 ? "+" : "-",
               fabs(note_index_frac) * 100.0);
        if (++found >= count)
        {
            break;
        }
    }
    free_(in_buffer);
    free_(sort_buffer);
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
            fprintf(stderr, "Usage: %s cut start length in-filename out-filename\n", argv[0]);
            return -1;
        }
        size_t start = (size_t)atoll(argv[2]);  // 0 for start of file
        size_t length = (size_t)atoll(argv[3]); // 1000 for 1000 samples (see sample rate)
        const char *in_filename = argv[4];
        const char *out_filename = argv[5];
        return cut(start, length, in_filename, out_filename);
    }

    if (strcmp(tool, "gram") == 0)
    {
        if (argc < 6)
        {
            fprintf(stderr, "Usage: %s gram window-exp step-seconds in-filename out-filename\n", argv[0]);
            return -1;
        }
        size_t window_exp = (size_t)atoll(argv[2]);  // 10 for 1024 samples
        double step_seconds = (double)atof(argv[3]); // 0.1 for 10 per second
        const char *in_filename = argv[4];
        const char *out_filename = argv[5];
        size_t channel = 0;
        return gram(window_exp, step_seconds, in_filename, out_filename, channel);
    }

    if (strcmp(tool, "fft") == 0)
    {
        if (argc < 6)
        {
            fprintf(stderr, "Usage: %s fft start window-exp in-filename out-filename\n", argv[0]);
            return -1;
        }
        size_t start = (size_t)atoll(argv[2]);      // 0 for start of file
        size_t window_exp = (size_t)atoll(argv[3]); // 10 for 1024 samples
        const char *in_filename = argv[4];
        const char *out_filename = argv[5];
        size_t channel = 0;
        size_t height = 512;
        double db_range = 160.0;
        return fft(start, window_exp, in_filename, out_filename, channel, height, db_range);
    }

    if (strcmp(tool, "scope") == 0)
    {
        if (argc < 7)
        {
            fprintf(stderr, "Usage: %s scope start frequency periods in-filename out-filename\n", argv[0]);
            return -1;
        }
        size_t start = (size_t)atoll(argv[2]);    // 0 for start of file
        double frequency = (double)atof(argv[3]); // 440.0 for A4
        size_t periods = (size_t)atoll(argv[4]);  // 1 for one period
        const char *in_filename = argv[5];
        const char *out_filename = argv[6];
        size_t channel = 0;
        size_t height = 512;
        return scope(start, frequency, periods, in_filename, out_filename, channel, height);
    }

    if (strcmp(tool, "peaks") == 0)
    {
        if (argc < 5)
        {
            fprintf(stderr, "Usage: %s peaks start window-exp filename\n", argv[0]);
            return -1;
        }
        size_t start = (size_t)atoll(argv[2]);      // 0 for start of file
        size_t window_exp = (size_t)atoll(argv[3]); // 10 gives decent results
        const char *filename = argv[4];
        size_t channel = 0;
        size_t count = 10;
        return peaks(start, window_exp, filename, channel, count);
    }

    return error_type_message(csErrorInvalidArgument, "Unknown tool: %s", tool);
}