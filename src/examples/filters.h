#include "../core/funcs.h"

func filters()
{
    func input = noise();
    func each = _(1);
    int count = 8;
    func lows = comp(
        low_pass(input, mul_(A0, .0625)), each,
        low_pass(input, mul_(A0, .125)), each,
        low_pass(input, mul_(A0, .25)), each,
        low_pass(input, mul_(A0, .5)), each,
        low_pass(input, A0), each,
        low_pass(input, A1), each,
        low_pass(input, A2), each,
        low_pass(input, A3), each);
    func highs = comp(
        high_pass(input, mul_(A10, 16)), each,
        high_pass(input, mul_(A10, 8)), each,
        high_pass(input, mul_(A10, 4)), each,
        high_pass(input, mul_(A10, 2)), each,
        high_pass(input, A10), each,
        high_pass(input, A9), each,
        high_pass(input, A8), each,
        high_pass(input, A7), each);
    func composition = comp(
        mul_(sine(A3), .25), _(1), lows, mul_(each, count),
        mul_(sine(A3), .25), _(1), highs, mul_(each, count));
    func looped = loop_(composition, 2 * count + 2);
    func scaled = mul_(looped, .1);
    return scaled;
}
