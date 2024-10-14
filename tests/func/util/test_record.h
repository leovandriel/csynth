#include "../../../src/func/gen/const.h"
#include "../../../src/func/op/sum.h"
#include "../../../src/func/util/record.h"
#include "../../util/test.h"

void test_record(void)
{
    char buffer[1024] = {0};
    FILE *file = fmemopen_(buffer, sizeof(buffer), "wb");
    Gen *gen = gen_create(record_create(file, 10, 1, (Func *[]){sum_create(const_create(0.1))}));
    assert_double_equal(gen_eval(gen, NULL), 0.0);
    assert_double_equal(gen_eval(gen, NULL), 0.1);
    assert_double_equal(gen_eval(gen, NULL), 0.2);
    assert_double_equal(gen_eval(gen, NULL), 0.3);
    gen_free(gen);
    WavHeader header = *(WavHeader *)buffer;
    size_t sample_count = 0;
    size_t channel_count = 0;
    size_t sample_rate = 0;
    assert_long_equal(wav_header_read(&header, &sample_count, &channel_count, &sample_rate), csErrorNone);
    assert_long_equal(sample_count, 4);
    assert_long_equal(channel_count, 1);
    assert_long_equal(sample_rate, 10);
    sample_t *data = (sample_t *)(buffer + sizeof(header));
    assert_long_equal(data[0], 0);
    assert_long_equal(data[1], 1638);
    assert_long_equal(data[2], 3276);
    assert_long_equal(data[3], 4915);
    func_free();
}
