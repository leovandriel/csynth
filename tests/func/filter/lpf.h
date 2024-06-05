#include "../../../src/func/filter/lpf.h"
#include "../../util/test.h"

void test_lpf()
{
    Func *t = lpf(const_(1), const_(10));
    Gen *g = gen_create(t, 0.1);
    assert_gen_equal(g, 0.0000000000000000);
    assert_gen_equal(g, 0.8626974383015871);
    assert_gen_equal(g, 0.9811480065510535);
    assert_gen_equal(g, 0.9974115730063380);
    assert_gen_equal(g, 0.9996446023430009);
    assert_gen_equal(g, 0.9999512029912724);
    assert_gen_equal(g, 0.9999933000456985);
    assert_gen_equal(g, 0.9999990800791111);
    assert_gen_equal(g, 0.9999998736925054);
    assert_gen_equal(g, 0.9999999826576574);
    assert_gen_equal(g, 0.9999999976188519);
    assert_gen_equal(g, 0.9999999996730623);
}
