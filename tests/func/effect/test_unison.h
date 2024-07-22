#include "../../../src/func/effect/unison.h"
#include "../../../src/func/gen/sample.h"
#include "../../../src/func/gen/saw.h"
#include "../../../src/util/random.h"
#include "../../util/test.h"

void test_unison(void)
{
    Gen *gen = gen_create(unison_create(5, saw_create(sample_create())));
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.1250077514196241);
    assert_double_equal(gen_eval(gen, NULL), 0.2500155028392481);
    assert_double_equal(gen_eval(gen, NULL), 0.3750232542588722);
    assert_double_equal(gen_eval(gen, NULL), 0.5000310056784962);
    assert_double_equal(gen_eval(gen, NULL), 0.6250387570981203);
    assert_double_equal(gen_eval(gen, NULL), 0.7500465085177445);
    assert_double_equal(gen_eval(gen, NULL), 0.8750542599373685);
    assert_double_equal(gen_eval(gen, NULL), -0.9999379886430075);
    assert_double_equal(gen_eval(gen, NULL), -0.8749302372233836);
    assert_double_equal(gen_eval(gen, NULL), -0.7499224858037595);
    assert_double_equal(gen_eval(gen, NULL), -0.6249147343841354);
    gen_free(gen);
    func_free();
}
