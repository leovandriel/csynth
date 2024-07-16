#include "../../src/util/rand.h"
#include "./test.h"

void test_rand(void)
{
    rand_seed(0);
    assert(rand_unsigned_long() == 1152992998833853505UL);
    assert(rand_unsigned_long() == 11177516664432764457UL);
    assert(rand_unsigned_long() == 17678023832001937445UL);
    assert(rand_uniform() == 0.52362249432221674716);
    assert(rand_uniform() == 0.96362799473474713973);
    assert(rand_uniform() == 0.63388067691606986286);
    assert(rand_range(0, 1) == 0.77411840881254556645);
    assert(rand_range(1, 2) == 1.48922748458651099667);
    assert(rand_range(-3, 7) == 1.51714985351188635931);
    assert(rand_gauss(0, 1) == 1.92496688266798221533);
    assert(rand_gauss(1, 2) == -1.81970181198147629153);
    assert(rand_gauss(-2, 3) == -0.74949711474660718479);
}
