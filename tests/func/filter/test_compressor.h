#include "../../../src/func/filter/compressor.h"
#include "../../../src/func/gen/const.h"
#include "../../../src/func/gen/uniform.h"
#include "../../util/test.h"

void test_compressor()
{
    Gen *gen = gen_create(compressor_create(const_(0.5), const_(0.1), const_(0.1), const_(0.1), uniform_create()));
    assert_double_equal(gen_eval(gen, NULL), -0.8704605766408398);
    assert_double_equal(gen_eval(gen, NULL), 0.2108759164371954);
    assert_double_equal(gen_eval(gen, NULL), 0.9076380602936124);
    assert_double_equal(gen_eval(gen, NULL), 0.0468244670055158);
    assert_double_equal(gen_eval(gen, NULL), 0.9145030047988004);
    assert_double_equal(gen_eval(gen, NULL), 0.2644291570750112);
    assert_double_equal(gen_eval(gen, NULL), 0.5415851683272676);
    assert_double_equal(gen_eval(gen, NULL), -0.0213085048651813);
    assert_double_equal(gen_eval(gen, NULL), -0.0956107510153559);
    assert_double_equal(gen_eval(gen, NULL), -0.7649327402278959);
    assert_double_equal(gen_eval(gen, NULL), 0.8576653355739587);
    assert_double_equal(gen_eval(gen, NULL), -0.3833428173223866);
    gen_free(gen);
    func_free();
}
