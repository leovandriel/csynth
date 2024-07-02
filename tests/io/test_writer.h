#include "../../src/func/gen/const.h"
#include "../../src/io/writer.h"
#include "../util/test.h"

void test_writer()
{
    write(1, "output/test.wav", const_(1));
}
