#include "../../src/util/rand.h"
#include "./test.h"

void test_rand(void)
{
    Random random = random_create(0);
    assert(random_unsigned_long(&random) == 1152992998833853505UL);
    assert(random_unsigned_long(&random) == 11177516664432764457UL);
    assert(random_unsigned_long(&random) == 17678023832001937445UL);
    assert(random_uniform(&random) == 0.52362249432221674716);
    assert(random_uniform(&random) == 0.96362799473474713973);
    assert(random_uniform(&random) == 0.63388067691606986286);
    assert(random_range(&random, 0, 1) == 0.77411840881254556645);
    assert(random_range(&random, 1, 2) == 1.48922748458651099667);
    assert(random_range(&random, -3, 7) == 1.51714985351188635931);
    assert(random_gauss(&random, 0, 1) == 1.92496688266798221533);
    assert(random_gauss(&random, 1, 2) == -1.81970181198147629153);
    assert(random_gauss(&random, -2, 3) == -0.74949711474660718479);
}
