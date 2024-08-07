#include "../../src/util/random.h"
#include "./test.h"

void test_random(void)
{
    Random random = random_create(0);
    assert_long_equal(random_unsigned_long(&random), 1152992998833853505UL);
    assert_long_equal(random_unsigned_long(&random), 11177516664432764457UL);
    assert_long_equal(random_unsigned_long(&random), 17678023832001937445UL);
    assert_double_equal(random_uniform(&random), 0.52362249432221674716);
    assert_double_equal(random_uniform(&random), 0.96362799473474713973);
    assert_double_equal(random_uniform(&random), 0.63388067691606986286);
    assert_double_equal(random_uniform_range(&random, 0, 1), 0.77411840881254556645);
    assert_double_equal(random_uniform_range(&random, 1, 2), 1.48922748458651099667);
    assert_double_equal(random_uniform_range(&random, -3, 7), 1.51714985351188635931);
    assert_double_equal(random_gauss_range(&random, 0, 1), 1.92496688266798221533);
    assert_double_equal(random_gauss_range(&random, 1, 2), -1.81970181198147629153);
    assert_double_equal(random_gauss_range(&random, -2, 3), -0.74949711474660718479);
}
