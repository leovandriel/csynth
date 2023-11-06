#include "./beep_boop.h"
#include "./beats.h"
#include "./shapes.h"
#include "./filters.h"
#include "./lows.h"
#include "./guitar.h"
#include "./beep_boop_dynamic.h"

func all_examples()
{
    func examples = comp_rel(
        print("beep boop", beep_boop()), _(8),
        print("beats", beats()), _(8),
        print("shapes", shapes()), _(8),
        print("guitar", guitar()), _(24),
        print("lows", lows()), _(30),
        print("filters", filters()), _(30),
        print("beep boop increase", beep_boop_increase()), _(8));
    return examples;
}
