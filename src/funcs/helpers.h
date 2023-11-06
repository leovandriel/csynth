//
// helpers.h - A collection of convenience macros
//
// Provides:
// - ZERO - A constant function, which always returns 0
// - ONE - A constant function, which always returns 1
// - clamp(value, min, max) - Ensure value is clipped to [min, max]
// - block(edge0, edge1) - A block function, which is 1 between edge0 and edge1
// - hump(edge0, edge1, edge2, edge3) - A smooth block function, which is 1
//   between edge1 and edge2 and 0 before edge0 and after edge3
// - clamp_, block_, hump_ - Take double arguments instead of functions
//
#ifndef COMPOSER_HELPERS_H
#define COMPOSER_HELPERS_H

#include "cons.h"
#include "neg.h"
#include "mul.h"
#include "smooth.h"
#include "step.h"

#define ZERO cons(0.0)
#define ONE cons(1.0)

#define clamp(_value, _min, _max) min(max(_value, _min), _max)
#define clamp_(_value, _min, _max) clamp(_value, cons(_min), cons(_max))

#define block(_edge0, _edge1) mul(step(_edge0), add(ONE, neg(step(_edge1))))
#define block_(_edge0, _edge1) block(cons(_edge0), cons(_edge1))

#define hump(_edge0, _edge1, _edge2, _edge3) mul(smooth(_edge0, _edge1), add(ONE, neg(smooth(_edge2, _edge3))))
#define hump_(_edge0, _edge1, _edge2, _edge3) hump(cons(_edge0), cons(_edge1), cons(_edge2), cons(_edge3))

#endif // COMPOSER_HELPERS_H
