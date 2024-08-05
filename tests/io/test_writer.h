#include "../../src/func/gen/const.h"
#include "../../src/func/gen/saw.h"
#include "../../src/io/writer.h"
#include "../util/test.h"

void test_writer(void)
{
    Func *channels[] = {saw_create(const_create(0.1))};
    char buffer[1024] = {0};
    FILE *file = fmemopen(buffer, sizeof(buffer), "w");
    assert_long_equal(writer_write_channels(1.0, file, 10, 1, channels), csErrorNone);
    assert_long_equal(fclose(file), 0);
    WavHeader header = *(WavHeader *)buffer;
    size_t sample_count = 0;
    size_t channel_count = 0;
    size_t sample_rate = 0;
    assert_long_equal(wav_header_read(&header, &sample_count, &channel_count, &sample_rate), csErrorNone);
    assert_long_equal(sample_count, 10);
    assert_long_equal(channel_count, 1);
    assert_long_equal(sample_rate, 10);
    sample_t *data = (sample_t *)(buffer + sizeof(header));
    assert_long_equal(data[0], 0);
    assert_long_equal(data[1], 3276);
    assert_long_equal(data[2], 6553);
    assert_long_equal(data[3], 9830);
    assert_long_equal(data[4], 13106);
    assert_long_equal(data[5], 16383);
    assert_long_equal(data[6], -13106);
    assert_long_equal(data[7], -9830);
    assert_long_equal(data[8], -6553);
    assert_long_equal(data[9], -3276);
    assert_long_equal(data[10], 0);
}
