#include "../core/funcs.h"

func filters()
{
    func input = noise();
    func each = _(1);
    int count = 8;
    func lows = comp(
        low_pass(input, mul(A0, _(.0625))), each,
        low_pass(input, mul(A0, _(.125))), each,
        low_pass(input, mul(A0, _(.25))), each,
        low_pass(input, mul(A0, _(.5))), each,
        low_pass(input, A0), each,
        low_pass(input, A1), each,
        low_pass(input, A2), each,
        low_pass(input, A3), each);
    func highs = comp(
        high_pass(input, mul(A10, _(16))), each,
        high_pass(input, mul(A10, _(8))), each,
        high_pass(input, mul(A10, _(4))), each,
        high_pass(input, mul(A10, _(2))), each,
        high_pass(input, A10), each,
        high_pass(input, A9), each,
        high_pass(input, A8), each,
        high_pass(input, A7), each);
    func composition = comp(
        mul(sine(A3), _(.25)), _(1), lows, mul(each, _(count)),
        mul(sine(A3), _(.25)), _(1), highs, mul(each, _(count)));
    func looped = loop(composition, _(2 * count + 2));
    func scaled = mul(looped, _(.1));
    return scaled;
}
