#include "./examples/beep_boop.h"
#include "./examples/beats.h"
#include "./examples/shapes.h"
#include "./examples/filters.h"
#include "./examples/lows.h"
#include "./examples/beep_boop_dynamic.h"

#include "./core/writer.h"

int main(void)
{
    write(beep_boop(), 8);
    // write(beats(), 16);
    // write(shapes(), 15);
    // write(filters(), 30);
    // write(lows(), 30);
    // write(beep_boop_increase(), 8);
    return 0;
}
