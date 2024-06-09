#include "../../../src/func/gen/sine.h"
#include "../../../src/func/gen/timer.h"
#include "../../util/test.h"

void test_sine_const()
{
    Func *time = sine(const_(1));
    Gen *gen = gen_create(time, 0.1);
    assert_gen_equal(gen, 0.0000000000000000);
    assert_gen_equal(gen, 0.5877852419187400);
    assert_gen_equal(gen, 0.9510565051057910);
    assert_gen_equal(gen, 0.9510565051057910);
    assert_gen_equal(gen, 0.5877852419187400);
    assert_gen_equal(gen, -0.0000000000000000);
    assert_gen_equal(gen, -0.5877852419187400);
    assert_gen_equal(gen, -0.9510565051057910);
    assert_gen_equal(gen, -0.9510565051057910);
    assert_gen_equal(gen, -0.5877852419187400);
    assert_gen_equal(gen, 0.0000000000000000);
    assert_gen_equal(gen, 0.5877852419187400);
}

void test_sine_timer()
{
    Func *time = sine(timer());
    Gen *gen = gen_create(time, 0.1);
    assert_gen_equal(gen, 0.0000000000000000);
    assert_gen_equal(gen, 0.0000000000000000);
    assert_gen_equal(gen, 0.0314107589087103);
    assert_gen_equal(gen, 0.1045284627888829);
    assert_gen_equal(gen, 0.2181432374437673);
    assert_gen_equal(gen, 0.3681245516448899);
    assert_gen_equal(gen, 0.5446390303877368);
    assert_gen_equal(gen, 0.7289686234765415);
    assert_gen_equal(gen, 0.8910065137048342);
    assert_gen_equal(gen, 0.9892723178837863);
    assert_gen_equal(gen, 0.9759167442563212);
    assert_gen_equal(gen, 0.8090169800974962);
}

void test_sine()
{
    test_sine_const();
    test_sine_timer();
}
