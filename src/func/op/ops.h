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
#include "./prod.h"
#include "./sin.h"
#include "./smooth.h"
#include "./step.h"
#include "./sum.h"
#include "./tanh.h"

/** @brief Macro to create an addition function with variable arguments */
#define add(...) (add_create(ARGS_FUNC(__VA_ARGS__)))
/** @brief Creates an addition function that adds a constant value to an input */
Func *add_(double value, Func *input) { return add(const_(value), input); }
/** @brief Creates a negation function that outputs -input */
Func *neg(Func *input) { return neg_create(input); }
/** @brief Creates a subtraction function that outputs lhs - rhs */
Func *sub(Func *lhs, Func *rhs) { return add(lhs, neg(rhs)); }
/** @brief Creates a subtraction function that subtracts a constant from the input */
Func *sub_(Func *lhs, double rhs) { return sub(lhs, const_(rhs)); }

/** @brief Macro to create a multiplication function with variable arguments */
#define mul(...) (mul_create(ARGS_FUNC(__VA_ARGS__)))
/** @brief Creates a multiplication function that multiplies input by a constant value */
Func *mul_(double value, Func *input) { return mul(const_(value), input); }
/** @brief Creates an inversion function that outputs 1/input */
Func *inv(Func *input) { return inv_create(input); }
/** @brief Creates a division function that outputs lhs/rhs */
Func *dvd(Func *lhs, Func *rhs) { return mul(lhs, inv(rhs)); }
/** @brief Creates a division function that outputs lhs/rhs */
Func *dvd_(Func *lhs, double rhs) { return dvd(lhs, const_(rhs)); }
/** @brief Creates an average function that outputs the mean of multiple inputs */
Func *avg_create(size_t count, Func **inputs) { return mul_create(ARGS_FUNC(add_create(count, inputs), const_(1.0 / (double)count))); }
/** @brief Macro to create an average function with variable arguments */
#define avg(...) (avg_create(ARGS_FUNC(__VA_ARGS__)))

/** @brief Creates a power function that outputs base^exponent */
Func *pow_op(Func *base, Func *exponent) { return pow_create(base, exponent); }
/** @brief Creates a power function with constant exponent */
Func *pow_op_(double exponent, Func *input) { return pow_op(const_(exponent), input); }
/** @brief Creates a square function that outputs input^2 */
Func *sq(Func *input) { return pow_op(input, const_(2)); }
/** @brief Creates a square root function that outputs input^0.5 */
Func *sqr(Func *input) { return pow_op(input, const_(0.5)); }
/** @brief Creates an exponential function that outputs e^input */
Func *expo(Func *input) { return pow_op(const_(M_E), input); }
/** @brief Creates an exponential function that outputs 2^input */
Func *expo2(Func *input) { return pow_op(const_(2), input); }

/** @brief Creates a sine function that outputs sin(input) */
Func *sin_op(Func *input) { return sin_create(input); }
/** @brief Creates a hyperbolic tangent function that outputs tanh(input) */
Func *tanh_op(Func *input) { return tanh_create(input); }
/** @brief Creates a summation function that outputs the sum of all samples */
Func *sum(Func *input) { return sum_create(input); }
/** @brief Creates a product function that outputs the product of all samples */
Func *prod(Func *input) { return prod_create(input); }

/** @brief Macro to create a minimum function with variable arguments */
#define min(...) (min_create(ARGS_FUNC(__VA_ARGS__)))
/** @brief Creates a minimum function comparing against a constant maximum */
Func *min_(double max, Func *input) { return min(const_(max), input); }
/** @brief Macro to create a maximum function with variable arguments */
#define max(...) (max_create(ARGS_FUNC(__VA_ARGS__)))
/** @brief Creates a maximum function comparing against a constant minimum */
Func *max_(double min, Func *input) { return max(const_(min), input); }
/** @brief Creates a clamp function that constrains input between min and max */
Func *clamp(Func *min, Func *max, Func *input) { return max(min, min(max, input)); }
/** @brief Creates a clamp function with constant min and max values */
Func *clamp_(double min, double max, Func *input) { return clamp(const_(min), const_(max), input); }

/** @brief Creates a step function that outputs 0 when input < edge, 1 otherwise */
Func *step_op(Func *edge, Func *input) { return step_create(edge, input); }
/** @brief Creates a step function with constant edge value */
Func *step_op_(double edge, Func *input) { return step_op(const_(edge), input); }
/** @brief Creates a smooth step function that smoothly transitions between 0 and 1 */
Func *smooth_op(Func *edge0, Func *edge1, Func *input) { return smooth_create(edge0, edge1, input); }
/** @brief Creates a smooth step function with constant edge values */
Func *smooth_op_(double edge0, double edge1, Func *input) { return smooth_op(const_(edge0), const_(edge1), input); }

/** @brief Creates a linear interpolation function between left and right over span */
Func *linear_op(Func *span, Func *left, Func *right, Func *input) { return add(left, mul(sub(right, left), dvd(input, span))); }
/** @brief Creates a linear interpolation function with constant parameters */
Func *linear_op_(double span, double left, double right, Func *input) { return linear_op(const_(span), const_(left), const_(right), input); }
/** @brief Creates an exponential interpolation function between left and right over span */
Func *exponent_op(Func *span, Func *left, Func *right, Func *input) { return mul(left, pow_op(dvd(right, left), dvd(input, span))); }
/** @brief Creates an exponential interpolation function with constant parameters */
Func *exponent_op_(double span, double left, double right, Func *input) { return exponent_op(const_(span), const_(left), const_(right), input); }

/** @brief Converts unipolar [0,1] to bipolar [-1,1] range */
Func *ar(Func *input) { return sub_(mul_(2, input), 1); }
/** @brief Converts bipolar [-1,1] to unipolar [0,1] range */
Func *kr(Func *input) { return mul_(0.5, add_(1, input)); }
/** @brief Applies affine transformation after converting to unipolar range */
Func *kr_affine(Func *offset, Func *factor, Func *input) { return add(offset, mul(factor, kr(input))); }
/** @brief Applies affine transformation with constants after converting to unipolar range */
Func *kr_affine_(double offset, double factor, Func *input) { return kr_affine(const_(offset), const_(factor), input); }
/** @brief Scales input after converting to unipolar range */
Func *kr_scale(Func *factor, Func *input) { return mul(factor, kr(input)); }
/** @brief Scales input by constant after converting to unipolar range */
Func *kr_scale_(double factor, Func *input) { return kr_scale(const_(factor), input); }
/** @brief Maps input to range [min,max] after converting to unipolar */
Func *kr_range(Func *min, Func *max, Func *input) { return add(min, mul(sub(max, min), kr(input))); }
/** @brief Maps input to constant range [min,max] after converting to unipolar */
Func *kr_range_(double min, double max, Func *input) { return kr_range(const_(min), const_(max), input); }

#endif // CSYNTH_OPS_H
