#include "../../../src/func/filter/resonant.h"
#include "../../../src/func/gen/square.h"
#include "../../util/test.h"

void test_resonant()
{
    Func *time = resonant(square_(1), const_(2), const_(1));
    Gen *gen = gen_create(time, 0.1);
    assert_gen_equal(gen, 1.0000000000000000);
    assert_gen_equal(gen, -0.3554467621723905);
    assert_gen_equal(gen, 0.9140520393842109);
    assert_gen_equal(gen, 0.2068404594181049);
    assert_gen_equal(gen, 0.4179689937741931);
    assert_gen_equal(gen, -1.5283959570284307);
    assert_gen_equal(gen, 1.0572185263015357);
    assert_gen_equal(gen, -1.3835082994633348);
    assert_gen_equal(gen, -0.0165946039882035);
    assert_gen_equal(gen, -0.4292847808124328);
    assert_gen_equal(gen, 1.4713719443499034);
    assert_gen_equal(gen, -0.9997882077581405);
    gen_free(gen);
    func_free();
}
