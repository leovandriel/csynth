#include "../../../src/func/filter/biquad.h"
#include "../../../src/func/gen/const.h"
#include "../../../src/func/gen/uniform.h"
#include "../../../src/util/rand.h"
#include "../../util/test.h"

void test_lowpass()
{
    rand_seed(0);
    Func *time = biquad_create(BiquadTypeLowpass, const_(0.1), const_(1.0), NULL, uniform_create());
    Gen *gen = gen_create(time);
    Eval eval = eval_create(0.1);
    assert_double_equal(gen_eval(gen, &eval), -0.0645759339514222);
    assert_double_equal(gen_eval(gen, &eval), -0.1942688533481121);
    assert_double_equal(gen_eval(gen, &eval), -0.1733484419674942);
    assert_double_equal(gen_eval(gen, &eval), 0.0436664709297865);
    assert_double_equal(gen_eval(gen, &eval), 0.2922632671271426);
    assert_double_equal(gen_eval(gen, &eval), 0.5017643926034852);
    assert_double_equal(gen_eval(gen, &eval), 0.6163861445063290);
    assert_double_equal(gen_eval(gen, &eval), 0.5960693034269544);
    assert_double_equal(gen_eval(gen, &eval), 0.4391718331024244);
    assert_double_equal(gen_eval(gen, &eval), 0.1508576121159292);
    assert_double_equal(gen_eval(gen, &eval), -0.1081548339366444);
    assert_double_equal(gen_eval(gen, &eval), -0.1747287193090926);
    gen_free(gen);
    func_free();
}

void test_highpass()
{
    rand_seed(0);
    Func *time = biquad_create(BiquadTypeHighpass, const_(0.1), const_(1.0), NULL, uniform_create());
    Gen *gen = gen_create(time);
    Eval eval = eval_create(0.1);
    assert_double_equal(gen_eval(gen, &eval), -0.6116720258089448);
    assert_double_equal(gen_eval(gen, &eval), 0.6065471125005860);
    assert_double_equal(gen_eval(gen, &eval), 0.8252077465657540);
    assert_double_equal(gen_eval(gen, &eval), -0.3995288272383933);
    assert_double_equal(gen_eval(gen, &eval), 0.2729978002442773);
    assert_double_equal(gen_eval(gen, &eval), -0.5167862815714974);
    assert_double_equal(gen_eval(gen, &eval), -0.1381355629146545);
    assert_double_equal(gen_eval(gen, &eval), -0.4850992909031182);
    assert_double_equal(gen_eval(gen, &eval), -0.1853761443086120);
    assert_double_equal(gen_eval(gen, &eval), -0.3889457495140732);
    assert_double_equal(gen_eval(gen, &eval), 1.2408180392336634);
    assert_double_equal(gen_eval(gen, &eval), -0.2698861192066698);
    gen_free(gen);
    func_free();
}

void test_bandpass()
{
    rand_seed(0);
    Func *time = biquad_create(BiquadTypeBandpass, const_(0.1), const_(1.0), NULL, uniform_create());
    Gen *gen = gen_create(time);
    Eval eval = eval_create(0.1);
    assert_double_equal(gen_eval(gen, &eval), -0.1987442888200088);
    assert_double_equal(gen_eval(gen, &eval), -0.2004094740953807);
    assert_double_equal(gen_eval(gen, &eval), 0.2647958797924422);
    assert_double_equal(gen_eval(gen, &eval), 0.4031073449530401);
    assert_double_equal(gen_eval(gen, &eval), 0.3619949220980743);
    assert_double_equal(gen_eval(gen, &eval), 0.2827832428001522);
    assert_double_equal(gen_eval(gen, &eval), 0.0699862360334168);
    assert_double_equal(gen_eval(gen, &eval), -0.1325150433508139);
    assert_double_equal(gen_eval(gen, &eval), -0.3503657180914351);
    assert_double_equal(gen_eval(gen, &eval), -0.5369742133722095);
    assert_double_equal(gen_eval(gen, &eval), -0.2601841277672899);
    assert_double_equal(gen_eval(gen, &eval), 0.0552907767507133);
    gen_free(gen);
    func_free();
}

void test_notch()
{
    rand_seed(0);
    Func *time = biquad_create(BiquadTypeNotch, const_(0.1), const_(1.0), NULL, uniform_create());
    Gen *gen = gen_create(time);
    Eval eval = eval_create(0.1);
    assert_double_equal(gen_eval(gen, &eval), -0.6762479597603671);
    assert_double_equal(gen_eval(gen, &eval), 0.4122782591524741);
    assert_double_equal(gen_eval(gen, &eval), 0.6518593045982600);
    assert_double_equal(gen_eval(gen, &eval), -0.3558623563086067);
    assert_double_equal(gen_eval(gen, &eval), 0.5652610673714200);
    assert_double_equal(gen_eval(gen, &eval), -0.0150218889680124);
    assert_double_equal(gen_eval(gen, &eval), 0.4782505815916744);
    assert_double_equal(gen_eval(gen, &eval), 0.1109700125238361);
    assert_double_equal(gen_eval(gen, &eval), 0.2537956887938123);
    assert_double_equal(gen_eval(gen, &eval), -0.2380881373981441);
    assert_double_equal(gen_eval(gen, &eval), 1.1326632052970191);
    assert_double_equal(gen_eval(gen, &eval), -0.4446148385157626);
    gen_free(gen);
    func_free();
}

void test_peak()
{
    rand_seed(0);
    Func *time = biquad_create(BiquadTypePeak, const_(0.1), const_(1.0), const_(1.0), uniform_create());
    Gen *gen = gen_create(time);
    Eval eval = eval_create(0.1);
    assert_double_equal(gen_eval(gen, &eval), -0.8749922485803759);
    assert_double_equal(gen_eval(gen, &eval), 0.2118687850570933);
    assert_double_equal(gen_eval(gen, &eval), 0.9166551843907023);
    assert_double_equal(gen_eval(gen, &eval), 0.0472449886444335);
    assert_double_equal(gen_eval(gen, &eval), 0.9272559894694944);
    assert_double_equal(gen_eval(gen, &eval), 0.2677613538321398);
    assert_double_equal(gen_eval(gen, &eval), 0.5482368176250911);
    assert_double_equal(gen_eval(gen, &eval), -0.0215450308269779);
    assert_double_equal(gen_eval(gen, &eval), -0.0965700292976228);
    assert_double_equal(gen_eval(gen, &eval), -0.7750623507703536);
    assert_double_equal(gen_eval(gen, &eval), 0.8724790775297293);
    assert_double_equal(gen_eval(gen, &eval), -0.3893240617650492);
    gen_free(gen);
    func_free();
}

void test_lowshelf()
{
    rand_seed(0);
    Func *time = biquad_create(BiquadTypeLowshelf, const_(0.1), NULL, const_(1.0), uniform_create());
    Gen *gen = gen_create(time);
    Eval eval = eval_create(0.1);
    assert_double_equal(gen_eval(gen, &eval), -0.8749922485803759);
    assert_double_equal(gen_eval(gen, &eval), 0.2118687850570933);
    assert_double_equal(gen_eval(gen, &eval), 0.9166551843907023);
    assert_double_equal(gen_eval(gen, &eval), 0.0472449886444335);
    assert_double_equal(gen_eval(gen, &eval), 0.9272559894694943);
    assert_double_equal(gen_eval(gen, &eval), 0.2677613538321397);
    assert_double_equal(gen_eval(gen, &eval), 0.5482368176250911);
    assert_double_equal(gen_eval(gen, &eval), -0.0215450308269777);
    assert_double_equal(gen_eval(gen, &eval), -0.0965700292976226);
    assert_double_equal(gen_eval(gen, &eval), -0.7750623507703535);
    assert_double_equal(gen_eval(gen, &eval), 0.8724790775297294);
    assert_double_equal(gen_eval(gen, &eval), -0.3893240617650491);
    gen_free(gen);
    func_free();
}

void test_highshelf()
{
    rand_seed(0);
    Func *time = biquad_create(BiquadTypeHighshelf, const_(0.1), NULL, const_(1.0), uniform_create());
    Gen *gen = gen_create(time);
    Eval eval = eval_create(0.1);
    assert_double_equal(gen_eval(gen, &eval), -0.8749922485803759);
    assert_double_equal(gen_eval(gen, &eval), 0.2118687850570933);
    assert_double_equal(gen_eval(gen, &eval), 0.9166551843907023);
    assert_double_equal(gen_eval(gen, &eval), 0.0472449886444335);
    assert_double_equal(gen_eval(gen, &eval), 0.9272559894694943);
    assert_double_equal(gen_eval(gen, &eval), 0.2677613538321397);
    assert_double_equal(gen_eval(gen, &eval), 0.5482368176250911);
    assert_double_equal(gen_eval(gen, &eval), -0.0215450308269777);
    assert_double_equal(gen_eval(gen, &eval), -0.0965700292976226);
    assert_double_equal(gen_eval(gen, &eval), -0.7750623507703535);
    assert_double_equal(gen_eval(gen, &eval), 0.8724790775297294);
    assert_double_equal(gen_eval(gen, &eval), -0.3893240617650491);
    gen_free(gen);
    func_free();
}

void test_biquad()
{
    test_lowpass();
    test_highpass();
    test_bandpass();
    test_notch();
    test_peak();
    test_lowshelf();
    test_highshelf();
}