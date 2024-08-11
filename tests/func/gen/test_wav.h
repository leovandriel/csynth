#include "../../../src/func/gen/const.h"
#include "../../../src/func/gen/wav.h"
#include "../../util/test.h"

void test_wav(void)
{
    sample_t samples[] = {0, 32767, -32767, 1, -1};
    PcmBuffer buffer = {
        .samples = samples,
        .sample_count = 5,
        .channel_count = 1,
        .sample_rate = 10,
    };
    Gen *gen = gen_create(wav_create(buffer, false, 0, const_create(0.1)));
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 1.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), -1.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.0000305185094760);
    assert_double_equal(gen_eval(gen, NULL), -0.0000305185094760);
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    gen_free(gen);
    func_free();
}
