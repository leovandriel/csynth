#include "../../../src/func/gen/unison.h"
#include "../../../src/func/gen/saw.h"
#include "../../util/test.h"

void test_unison()
{
    rand_seed(0);
    Func *t = unison(const_(1), saw, 5, 0.1);
    Gen *g = gen_create(t, 0.1);
    assert_gen_equal(g, 0.0000000000000000);
    assert_gen_equal(g, 1.0245606539796270);
    assert_gen_equal(g, 2.0491213079592541);
    assert_gen_equal(g, 3.0736819619388811);
    assert_gen_equal(g, 4.0982426159185081);
    assert_gen_equal(g, -2.8771967301018644);
    assert_gen_equal(g, -3.8526360761222378);
    assert_gen_equal(g, -2.8280754221426103);
    assert_gen_equal(g, -1.8035147681629833);
    assert_gen_equal(g, -0.7789541141833560);
    assert_gen_equal(g, 0.2456065397962710);
    assert_gen_equal(g, 1.2701671937758980);
}
