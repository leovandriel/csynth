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
#include "./sin.h"
#include "./smooth.h"
#include "./step.h"
#include "./tanh.h"

#define add(...) (add_create(FUNCS(__VA_ARGS__)))
Func *add_(double value, Func *input) { return add(const_(value), input); }
Func *neg(Func *input) { return neg_create(input); }
Func *sub(Func *lhs, Func *rhs) { return add(lhs, neg(rhs)); }
Func *sub_(Func *lhs, double rhs) { return sub(lhs, const_(rhs)); }

#define mul(...) (mul_create(FUNCS(__VA_ARGS__)))
Func *mul_(double value, Func *input) { return mul(const_(value), input); }
Func *inv(Func *input) { return inv_create(input); }
Func *dvd(Func *lhs, Func *rhs) { return mul(lhs, inv(rhs)); }
Func *dvd_(Func *lhs, double rhs) { return dvd(lhs, const_(rhs)); }
Func *avg_create(size_t count, Func **inputs) { return dvd_(add_create(count, inputs), (double)count); }
#define avg(...) (avg_create(FUNCS(__VA_ARGS__)))

Func *pow_op(Func *base, Func *exponent) { return pow_create(base, exponent); }
Func *pow_op_(double exponent, Func *input) { return pow_op(const_(exponent), input); }
Func *sq(Func *input) { return pow_op(input, const_(2)); }
Func *sqr(Func *input) { return pow_op(input, const_(0.5)); }
Func *expo(Func *input) { return pow_op(const_(M_E), input); }
Func *expo2(Func *input) { return pow_op(const_(2), input); }

Func *sin_op(Func *input) { return sin_create(input); }
Func *tanh_op(Func *input) { return tanh_create(input); }

#define min(...) (min_create(FUNCS(__VA_ARGS__)))
Func *min_(double max, Func *input) { return min(const_(max), input); }
#define max(...) (max_create(FUNCS(__VA_ARGS__)))
Func *max_(double min, Func *input) { return max(const_(min), input); }
Func *clamp(Func *min, Func *max, Func *input) { return max(min, min(max, input)); }
Func *clamp_(double min, double max, Func *input) { return clamp(const_(min), const_(max), input); }

Func *step_op(Func *edge, Func *input) { return step_create(edge, input); }
Func *step_op_(double edge, Func *input) { return step_op(const_(edge), input); }
Func *smooth_op(Func *edge0, Func *edge1, Func *input) { return smooth_create(edge0, edge1, input); }
Func *smooth_op_(double edge0, double edge1, Func *input) { return smooth_op(const_(edge0), const_(edge1), input); }

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
