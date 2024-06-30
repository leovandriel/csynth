//
// envelopes.h - Misc envelopes
//
#ifndef CSYNTH_ENVELOPES_H
#define CSYNTH_ENVELOPES_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../gen/const.h"
#include "../gen/gens.h"
#include "../op/adsr.h"
#include "../op/inv.h"
#include "../op/neg.h"
#include "../op/ops.h"
#include "../op/smooth.h"
#include "../op/step.h"
#include "../time/times.h"

Func *decay_env(Func *factor) { return expo(dvd(neg(pitch_timer_(1)), factor)); }
Func *decay_env_(double factor) { return decay_env(const_(factor)); }
Func *decay(Func *factor, Func *input) { return mul(decay_env(factor), input); }
Func *decay_(double factor, Func *input) { return decay(const_(factor), input); }

Func *decay_from_env(Func *factor, Func *left, Func *right) { return add(mul(decay_env(factor), sub(left, right)), right); }
Func *decay_from_env_(double factor, double left, double right) { return decay_from_env(const_(factor), const_(left), const_(right)); }
Func *decay_from(Func *factor, Func *left, Func *right, Func *input) { return mul(decay_from_env(factor, left, right), input); }
Func *decay_from_(double factor, double left, double right, Func *input) { return decay_from(const_(factor), const_(left), const_(right), input); }

Func *linear_env(Func *span, Func *left, Func *right) { return linear_op(span, left, right, pitch_timer_(1)); }
Func *linear_env_(double span, double left, double right) { return linear_env(const_(span), const_(left), const_(right)); }
Func *linear(Func *span, Func *left, Func *right, Func *input) { return mul(linear_env(span, left, right), input); }
Func *linear_(double span, double left, double right, Func *input) { return linear(const_(span), const_(left), const_(right), input); }

Func *exponent_env(Func *span, Func *left, Func *right) { return exponent_op(span, left, right, pitch_timer_(1)); }
Func *exponent_env_(double span, double left, double right) { return exponent_env(const_(span), const_(left), const_(right)); }
Func *exponent(Func *span, Func *left, Func *right, Func *input) { return mul(span, exponent_env(left, right, input)); }
Func *exponent_(double span, double left, double right, Func *input) { return exponent(const_(span), const_(left), const_(right), input); }

Func *step_env(Func *edge) { return step_op(edge, pitch_timer_(1)); }
Func *step_env_(double edge) { return step_env(const_(edge)); }
Func *step(Func *edge, Func *input) { return mul(step_env(edge), input); }
Func *step_(double edge, Func *input) { return step(const_(edge), input); }

Func *step_inv_env(Func *edge) { return sub(ONE, step_env(edge)); }
Func *step_inv_env_(double edge) { return step_inv_env(const_(edge)); }
Func *step_inv(Func *edge, Func *input) { return mul(step_inv_env(edge), input); }
Func *step_inv_(double edge, Func *input) { return step_inv(const_(edge), input); }

Func *rect_env(Func *edge0, Func *edge1) { return mul(step_env(edge0), step_inv_env(edge1)); }
Func *rect_env_(double edge0, double edge1) { return rect_env(const_(edge0), const_(edge1)); }
Func *rect(Func *edge0, Func *edge1, Func *input) { return mul(rect_env(edge0, edge1), input); }
Func *rect_(double edge0, double edge1, Func *input) { return rect(const_(edge0), const_(edge1), input); }

Func *smooth_env(Func *edge0, Func *edge1) { return smooth_op(edge0, edge1, pitch_timer_(1)); }
Func *smooth_env_(double edge0, double edge1) { return smooth_env(const_(edge0), const_(edge1)); }
Func *smooth(Func *edge0, Func *edge1, Func *input) { return mul(smooth_env(edge0, edge1), input); }
Func *smooth_(double edge0, double edge1, Func *input) { return smooth(const_(edge0), const_(edge1), input); }

Func *smooth_inv_env(Func *edge0, Func *edge1) { return sub(ONE, smooth_env(edge0, edge1)); }
Func *smooth_inv_env_(double edge0, double edge1) { return smooth_inv_env(const_(edge0), const_(edge1)); }
Func *smooth_inv(Func *edge0, Func *edge1, Func *input) { return mul(smooth_inv_env(edge0, edge1), input); }
Func *smooth_inv_(double edge0, double edge1, Func *input) { return smooth_inv(const_(edge0), const_(edge1), input); }

Func *rounded_env(Func *edge0, Func *edge1, Func *edge2, Func *edge3) { return mul(smooth_env(edge0, edge1), smooth_inv_env(edge2, edge3)); }
Func *rounded_env_(double edge0, double edge1, double edge2, double edge3) { return rounded_env(const_(edge0), const_(edge1), const_(edge2), const_(edge3)); }
Func *rounded(Func *edge0, Func *edge1, Func *edge2, Func *edge3, Func *input) { return mul(rounded_env(edge0, edge1, edge2, edge3), input); }
Func *rounded_(double edge0, double edge1, double edge2, double edge3, Func *input) { return rounded(const_(edge0), const_(edge1), const_(edge2), const_(edge3), input); }

Func *adsr_env(Func *attack, Func *decay, Func *sustain, Func *release, Func *duration) { return adsr_op(pitch_timer_(1), attack, decay, sustain, release, duration); }
Func *adsr_env_(double attack, double decay, double sustain, double release, double duration) { return adsr_env(const_(attack), const_(decay), const_(sustain), const_(release), const_(duration)); }
Func *adsr(Func *attack, Func *decay, Func *sustain, Func *release, Func *duration, Func *input) { return mul(adsr_env(attack, decay, sustain, release, duration), input); }
Func *adsr_(double attack, double decay, double sustain, double release, double duration, Func *input) { return adsr(const_(attack), const_(decay), const_(sustain), const_(release), const_(duration), input); }

#endif // CSYNTH_ENVELOPES_H
