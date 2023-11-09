#include "./beep_boop.h"
#include "./drummer.h"
#include "./dynamic.h"
#include "./example.h"
#include "./guitar.h"
#include "./simple_fm.h"

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
    EXAMPLE_CASE(simple_fm, 5)
    EXAMPLE_CASE(drummer, 10)
    EXAMPLE_CASE(guitar, 24)
    EXAMPLE_CASE(modulate_pitch, 10)
    EXAMPLE_CASE(modulate_speed, 10)
    EXAMPLE_CASE(example, 6)
    func examples = comp_rel_array(index, array);
    return examples;
}
