#include "../../../src/func/effect/unison.h"
#include "../../../src/func/gen/sample.h"
#include "../../../src/func/gen/saw.h"
#include "../../../src/util/rand.h"
#include "../../util/test.h"

void test_unison()
{
    rand_seed(0);
    Gen *gen = gen_create(unison_create(5, saw_create(sample_create())));
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), -0.3543934602037305);
    assert_double_equal(gen_eval(gen, NULL), 0.0912130795925390);
    assert_double_equal(gen_eval(gen, NULL), -0.2631803806111916);
    assert_double_equal(gen_eval(gen, NULL), 0.1824261591850779);
    assert_double_equal(gen_eval(gen, NULL), -0.1719673010186527);
    assert_double_equal(gen_eval(gen, NULL), -0.1263607612223832);
    assert_double_equal(gen_eval(gen, NULL), -0.0807542214261137);
    assert_double_equal(gen_eval(gen, NULL), -0.4351476816298442);
    assert_double_equal(gen_eval(gen, NULL), -0.3895411418335748);
    assert_double_equal(gen_eval(gen, NULL), -0.3439346020373054);
    assert_double_equal(gen_eval(gen, NULL), -0.6983280622410359);
    gen_free(gen);
    func_free();
}
