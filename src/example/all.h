#include "./beep_boop.h"
#include "./beats.h"
#include "./shapes.h"
#include "./guitar.h"
#include "./lows.h"
#include "./filters.h"
#include "./dynamic.h"
#include "./spangled.h"

#define EXAMPLE_CASE(_name, _duration)             \
    if (name == NULL || strcmp(name, #_name) == 0) \
    {                                              \
        array[index++] = print(#_name, _name());   \
        array[index++] = const_(_duration);        \
        *length += _duration;                      \
    }

func all_examples(const char *name, double *length)
{
    func array[100];
    int index = 0;
    EXAMPLE_CASE(beep_boop, 8)
    EXAMPLE_CASE(beats, 8)
    EXAMPLE_CASE(shapes, 8)
    EXAMPLE_CASE(guitar, 24)
    EXAMPLE_CASE(lows, 20)
    EXAMPLE_CASE(filters, 20)
    EXAMPLE_CASE(increase_pitch, 10)
    EXAMPLE_CASE(increase_speed, 10)
    EXAMPLE_CASE(wobble_both, 10)
    EXAMPLE_CASE(spangled, 78)
    func examples = comp_rel_array(index, array);
    return examples;
}
