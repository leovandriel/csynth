//
// ops.h - Various mathematical operators
//
// - clamp(value, min, max) - Ensure value is clipped to [min, max]
// - clamp_ - Take double arguments instead of functions
//
#ifndef CSYNTH_OPS_H
#define CSYNTH_OPS_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../gen/const.h"
#include "./add.h"
#include "./inv.h"
#include "./max.h"
#include "./min.h"
#include "./mul.h"
#include "./neg.h"
#include "./pow.h"

Func *dvd(Func *lhs, Func *rhs) { return mul(lhs, inv(rhs)); }
Func *dvd_(Func *lhs, double rhs) { return dvd(lhs, const_(rhs)); }

Func *sq(Func *input) { return pow_op(input, const_(2)); }
Func *sqr(Func *input) { return pow_op(input, const_(0.5)); }
Func *expo(Func *input) { return pow_op(const_(M_E), input); }
Func *expo2(Func *input) { return pow_op(const_(2), input); }

Func *clamp(Func *min, Func *max, Func *input) { return max(min, min(max, input)); }
Func *clamp_(double min, double max, Func *input) { return clamp(const_(min), const_(max), input); }

Func *sub(Func *lhs, Func *rhs) { return add(lhs, neg(rhs)); }
Func *sub_(Func *lhs, double rhs) { return sub(lhs, const_(rhs)); }

Func *linear_op(Func *span, Func *left, Func *right, Func *input) { return add(left, mul(sub(right, left), dvd(input, span))); }
Func *linear_op_(double span, double left, double right, Func *input) { return linear_op(const_(span), const_(left), const_(right), input); }

Func *exponent_op(Func *span, Func *left, Func *right, Func *input) { return mul(left, pow_op(dvd(right, left), dvd(input, span))); }
Func *exponent_op_(double span, double left, double right, Func *input) { return exponent_op(const_(span), const_(left), const_(right), input); }

Func *ar(Func *input) { return sub_(mul_(2, input), 1); }

Func *kr(Func *input) { return dvd_(add_(1, input), 2); }
Func *kr_affine(Func *offset, Func *factor, Func *input) { return add(offset, mul(factor, kr(input))); }
Func *kr_affine_(double offset, double factor, Func *input) { return kr_affine(const_(offset), const_(factor), input); }
Func *kr_scale(Func *factor, Func *input) { return mul(factor, kr(input)); }
Func *kr_scale_(double factor, Func *input) { return kr_scale(const_(factor), input); }
Func *kr_range(Func *min, Func *max, Func *input) { return add(min, mul(sub(max, min), kr(input))); }
Func *kr_range_(double min, double max, Func *input) { return kr_range(const_(min), const_(max), input); }

#endif // CSYNTH_OPS_H
