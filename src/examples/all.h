#include "./beep_boop.h"
#include "./beats.h"
#include "./shapes.h"
#include "./filters.h"
#include "./lows.h"
#include "./beep_boop_dynamic.h"

func all_examples()
{
    func examples = comp(
        print("beep boop", beep_boop()), cons(8),
        print("beats", beats()), cons(8),
        print("shapes", shapes()), cons(8),
        print("beep boop increase", beep_boop_increase()), cons(8),
        print("lows", lows()), cons(30),
        print("filters", filters()), cons(30));
    return examples;
}
