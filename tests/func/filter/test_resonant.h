#include "../../../src/func/filter/filters.h"
#include "../../../src/func/filter/resonant.h"
#include "../../../src/func/gen/square.h"
#include "../../../src/func/time/times.h"
#include "../../util/test.h"

void test_resonant()
{
    Gen *gen = gen_create(resonant(const_(2), const_(1), square_create(pitch_ticker_(1))));
    Eval eval = eval_create(0.1);
    assert_double_equal(gen_eval(gen, &eval), 1.0000000000000000);
    assert_double_equal(gen_eval(gen, &eval), -0.3554467621723905);
    assert_double_equal(gen_eval(gen, &eval), 0.9140520393842109);
    assert_double_equal(gen_eval(gen, &eval), 0.2068404594181049);
    assert_double_equal(gen_eval(gen, &eval), 0.4179689937741931);
    assert_double_equal(gen_eval(gen, &eval), -1.5283959570284307);
    assert_double_equal(gen_eval(gen, &eval), 1.0572185263015357);
    assert_double_equal(gen_eval(gen, &eval), -1.3835082994633348);
    assert_double_equal(gen_eval(gen, &eval), -0.0165946039882035);
    assert_double_equal(gen_eval(gen, &eval), -0.4292847808124328);
    assert_double_equal(gen_eval(gen, &eval), 1.4713719443499034);
    assert_double_equal(gen_eval(gen, &eval), -0.9997882077581405);
    gen_free(gen);
    func_free();
}
