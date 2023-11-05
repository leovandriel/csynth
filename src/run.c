#include "./examples/beep_boop.h"
#include "./examples/beats.h"
#include "./examples/shapes.h"
#include "./examples/filters.h"
#include "./examples/lows.h"
#include "./core/writer.h"

int main(void)
{
    write(beep_boop(), 8);
    // write(beats(), 16);
    // write(shapes(), 15);
    // write(filters(), 30);
    // write(lows(), 30);
    return 0;
}
