#include "../../src/util/rand.h"
#include "./test.h"

void test_rand()
{
    rand_seed(0);
    assert(rand_unsigned_long() == 1152992998833853505UL);
    assert(rand_unsigned_long() == 11177516664432764457UL);
    assert(rand_unsigned_long() == 17678023832001937445UL);
    assert(rand_range(0, 1) == 0.52362249432221674716);
    assert(rand_range(1, 2) == 1.96362799473474725076);
    assert(rand_range(-3, 7) == 3.33880676916069862869);
}
