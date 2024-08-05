#include "../../../src/func/gen/const.h"
#include "../../../src/func/op/sin.h"
#include "../../util/test.h"

void test_sin(void)
{
    Gen *gen1 = gen_create(sin_create(const_create(0)));
    Gen *gen2 = gen_create(sin_create(const_create(1)));
    Gen *gen3 = gen_create(sin_create(const_create(2)));
    assert_double_equal(gen_eval(gen1, NULL), 0.0);
    assert_double_equal(gen_eval(gen2, NULL), 0.8414709848078965);
    assert_double_equal(gen_eval(gen3, NULL), 0.9092974268256817);
    gen_free(gen1);
    gen_free(gen2);
    gen_free(gen3);
    func_free();
}
