#include "../../../src/func/filter/hpf.h"
#include "../../util/test.h"

void test_hpf()
{
    Func *t = hpf(const_(1), const_(10));
    Gen *g = gen_create(t, 0.1);
    assert_gen_equal(g, 0.0000000000000000);
    assert_gen_equal(g, 0.1373025616984130);
    assert_gen_equal(g, 0.0188519934489465);
    assert_gen_equal(g, 0.0025884269936620);
    assert_gen_equal(g, 0.0003553976569991);
    assert_gen_equal(g, 0.0000487970087276);
    assert_gen_equal(g, 0.0000066999543015);
    assert_gen_equal(g, 0.0000009199208889);
    assert_gen_equal(g, 0.0000001263074946);
    assert_gen_equal(g, 0.0000000173423426);
    assert_gen_equal(g, 0.0000000023811481);
    assert_gen_equal(g, 0.0000000003269377);
}
