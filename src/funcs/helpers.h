#ifndef COMPOSER_HELPERS_H
#define COMPOSER_HELPERS_H

#include "cons.h"
#include "minus.h"
#include "mul.h"
#include "smooth.h"
#include "step.h"

#define ZERO cons(0.0)
#define ONE cons(1.0)

#define clamp(_value, _min, _max) min(max(_value, _min), _max)
#define block(_edge0, _edge1) mul(step(cons(_edge0)), minus(ONE, step(cons(_edge1))))
#define hump(_edge0, _edge1, _edge2, _edge3) mul(smooth(cons(_edge0), cons(_edge1)), minus(ONE, smooth(cons(_edge2), cons(_edge3))))

#endif // COMPOSER_HELPERS_H
