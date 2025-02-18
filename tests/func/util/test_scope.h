#include "../../../src/func/gen/const.h"
#include "../../../src/func/util/scope.h"
#include "../../../src/util/logger.h"
#include "../../util/test.h"

void test_scope(void)
{
    logger_set_level(LoggerLevelError);
    Gen *gen = gen_create(scope_create(const_create(1), const_create(1), 1, 1.0, "output/test.ppm", 10, 10, 1));
    Eval eval = {0};
    eval.params[EvalParamPitchTick] = 1;
    assert_long_equal(gen_eval(gen, &eval), 1);
    gen_free(gen);
    func_free();
}
