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

Func *clamp(Func *input, Func *min, Func *max) { return min(max(input, min), max); }
Func *clamp_(Func *input, double min, double max) { return clamp(input, const_(min), const_(max)); }

Func *sub(Func *lhs, Func *rhs) { return add(lhs, neg(rhs)); }
Func *sub_(Func *lhs, double rhs) { return sub(lhs, const_(rhs)); }

Func *linear_op(Func *input, Func *left, Func *right, Func *span) { return add(mul(sub(right, left), dvd(input, span)), left); }
Func *linear_op_(Func *input, double left, double right, double span) { return linear_op(input, const_(left), const_(right), const_(span)); }

Func *exponent_op(Func *input, Func *left, Func *right, Func *span) { return mul(pow_op(dvd(right, left), dvd(input, span)), left); }
Func *exponent_op_(Func *input, double left, double right, double span) { return exponent_op(input, const_(left), const_(right), const_(span)); }

Func *ar(Func *input) { return sub_(mul_(input, 2), 1); }

Func *kr(Func *input) { return dvd_(add_(input, 1), 2); }
Func *kr_affine(Func *input, Func *offset, Func *factor) { return add(mul(kr(input), factor), offset); }
Func *kr_affine_(Func *input, double offset, double factor) { return kr_affine(input, const_(offset), const_(factor)); }
Func *kr_scale(Func *input, Func *factor) { return mul(kr(input), factor); }
Func *kr_scale_(Func *input, double factor) { return kr_scale(input, const_(factor)); }
Func *kr_range(Func *input, Func *min, Func *max) { return add(mul(kr(input), sub(max, min)), min); }
Func *kr_range_(Func *input, double min, double max) { return kr_range(input, const_(min), const_(max)); }

#endif // CSYNTH_OPS_H
