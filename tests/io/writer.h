#include "../../src/func/gen/const.h"
#include "../../src/io/writer.h"
#include "../util/test.h"

void test_writer()
{
    write(const_(1), 1, "output/test.wav");
}
