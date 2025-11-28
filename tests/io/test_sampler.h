#include "../../src/func/gen/const.h"
#include "../../src/func/gen/saw.h"
#include "../../src/io/sampler.h"
#include "../util/test.h"

void test_sampler(void)
{
    Func *inputs[] = {
        saw_create(const_create(0.1)),
        saw_create(const_create(0.2)),
    };
    Sampler *sampler = sampler_create(10, 2, inputs);
    sample_t buffer[8] = {0};
    sampler_sample(sampler, 8, buffer);
    assert_long_equal(buffer[0], 0);
    assert_long_equal(buffer[1], 0);
    assert_long_equal(buffer[2], 3276);
    assert_long_equal(buffer[3], 6553);
    assert_long_equal(buffer[4], 6553);
    assert_long_equal(buffer[5], 13107);
    assert_long_equal(buffer[6], 9830);
    assert_long_equal(buffer[7], -13107);
    sampler_free(sampler);
    func_free();
}
