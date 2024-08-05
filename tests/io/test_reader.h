#include "../../src/func/gen/const.h"
#include "../../src/func/gen/saw.h"
#include "../../src/io/reader.h"
#include "../../src/io/writer.h"
#include "../util/test.h"

void test_reader(void)
{
    Func *channels[] = {saw_create(const_create(0.1))};
    char buffer[1024] = {0};
    FILE *file1 = fmemopen(buffer, sizeof(buffer), "w");
    assert_long_equal(writer_write_channels(1.0, file1, 10, 1, channels), csErrorNone);
    assert_long_equal(fclose(file1), 0);
    FILE *file2 = fmemopen(buffer, sizeof(buffer), "r");
    PcmBuffer buffer2 = {0};
    assert_long_equal(reader_read_file(&buffer2, file2), csErrorNone);
    assert_long_equal(fclose(file2), 0);
    assert_long_equal(buffer2.sample_count, 10);
    assert_long_equal(buffer2.channel_count, 1);
    assert_long_equal(buffer2.sample_rate, 10);
    reader_free(&buffer2);
}
