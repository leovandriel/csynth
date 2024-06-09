#include "../../../src/func/gen/saw.h"
#include "../../../src/func/gen/unison.h"
#include "../../util/test.h"

void test_unison()
{
    rand_seed(0);
    Func *time = unison(const_(1), saw, 5, 0.1);
    Gen *gen = gen_create(time, 0.1);
    assert_gen_equal(gen, 0.0000000000000000);
    assert_gen_equal(gen, 0.2049121307959254);
    assert_gen_equal(gen, 0.4098242615918508);
    assert_gen_equal(gen, 0.6147363923877762);
    assert_gen_equal(gen, 0.8196485231837016);
    assert_gen_equal(gen, -0.5754393460203729);
    assert_gen_equal(gen, -0.7705272152244476);
    assert_gen_equal(gen, -0.5656150844285220);
    assert_gen_equal(gen, -0.3607029536325967);
    assert_gen_equal(gen, -0.1557908228366712);
    assert_gen_equal(gen, 0.0491213079592542);
    assert_gen_equal(gen, 0.2540334387551796);
}
