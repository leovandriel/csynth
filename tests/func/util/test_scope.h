#include "../../../src/func/gen/const.h"
#include "../../../src/func/util/scope.h"
#include "../../../src/util/logger.h"
#include "../../util/test.h"

void test_scope(void)
{
    logger_set_level(LoggerLevelError);
    RenderPipe pipe = {.width = 1, .height = 1};
    Gen *gen = gen_create(scope_create(const_create(1), const_create(1), 1, 1.0, &pipe));
    Eval eval = {0};
    eval.params[EvalParamPitchTick] = 1;
    assert_long_equal(gen_eval(gen, &eval), 1);
    gen_free(gen);
    func_free();
}
