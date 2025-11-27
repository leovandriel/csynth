#include "../../src/io/wav_header.h"
#include "../util/test.h"

void test_wav_header(void)
{
    WavHeader header = {0};
    wav_header_update(&header, 2, 1, 4);
    size_t sample_count = 0;
    size_t channel_count = 0;
    size_t sample_rate = 0;
    assert_long_equal(wav_header_parse(&header, &sample_count, &channel_count, &sample_rate), csErrorNone);
    assert_long_equal(sample_count, 2);
    assert_long_equal(channel_count, 1);
    assert_long_equal(sample_rate, 4);
}
