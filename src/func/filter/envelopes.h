//
// envelopes.h - Misc envelopes
//
#ifndef CSYNTH_ENVELOPES_H
#define CSYNTH_ENVELOPES_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../gen/const.h"
#include "../gen/gens.h"
#include "../gen/timer.h"
#include "../op/adsr.h"
#include "../op/inv.h"
#include "../op/neg.h"
#include "../op/ops.h"
#include "../op/smooth.h"
#include "../op/step.h"

Func *decay_env(Func *factor) { return expo(dvd(neg(timer()), factor)); }
Func *decay_env_(double factor) { return decay_env(const_(factor)); }
Func *decay(Func *input, Func *factor) { return mul(input, decay_env(factor)); }
Func *decay_(Func *input, double factor) { return decay(input, const_(factor)); }

Func *decay_from_env(Func *left, Func *right, Func *factor) { return add(mul(decay_env(factor), sub(left, right)), right); }
Func *decay_from_env_(double left, double right, double factor) { return decay_from_env(const_(left), const_(right), const_(factor)); }
Func *decay_from(Func *input, Func *left, Func *right, Func *factor) { return mul(input, decay_from_env(left, right, factor)); }
Func *decay_from_(Func *input, double left, double right, double factor) { return decay_from(input, const_(left), const_(right), const_(factor)); }

Func *linear_env(Func *left, Func *right, Func *span) { return linear_op(timer(), left, right, span); }
Func *linear_env_(double left, double right, double span) { return linear_env(const_(left), const_(right), const_(span)); }
Func *linear(Func *input, Func *left, Func *right, Func *span) { return mul(input, linear_env(left, right, span)); }
Func *linear_(Func *input, double left, double right, double span) { return linear(input, const_(left), const_(right), const_(span)); }

Func *step_env(Func *edge) { return step_op(timer(), edge); }
Func *step_env_(double edge) { return step_env(const_(edge)); }
Func *step(Func *input, Func *edge) { return mul(input, step_env(edge)); }
Func *step_(Func *input, double edge) { return step(input, const_(edge)); }

Func *step_inv_env(Func *edge) { return sub(ONE, step_env(edge)); }
Func *step_inv_env_(double edge) { return step_inv_env(const_(edge)); }
Func *step_inv(Func *input, Func *edge) { return mul(input, step_inv_env(edge)); }
Func *step_inv_(Func *input, double edge) { return step_inv(input, const_(edge)); }

Func *rect_env(Func *edge0, Func *edge1) { return mul(step_env(edge0), step_inv_env(edge1)); }
Func *rect_env_(double edge0, double edge1) { return rect_env(const_(edge0), const_(edge1)); }
Func *rect(Func *input, Func *edge0, Func *edge1) { return mul(input, rect_env(edge0, edge1)); }
Func *rect_(Func *input, double edge0, double edge1) { return rect(input, const_(edge0), const_(edge1)); }

Func *smooth_env(Func *edge0, Func *edge1) { return smooth_op(timer(), edge0, edge1); }
Func *smooth_env_(double edge0, double edge1) { return smooth_env(const_(edge0), const_(edge1)); }
Func *smooth(Func *input, Func *edge0, Func *edge1) { return mul(input, smooth_env(edge0, edge1)); }
Func *smooth_(Func *input, double edge0, double edge1) { return smooth(input, const_(edge0), const_(edge1)); }

Func *smooth_inv_env(Func *edge0, Func *edge1) { return sub(ONE, smooth_env(edge0, edge1)); }
Func *smooth_inv_env_(double edge0, double edge1) { return smooth_inv_env(const_(edge0), const_(edge1)); }
Func *smooth_inv(Func *input, Func *edge0, Func *edge1) { return mul(input, smooth_inv_env(edge0, edge1)); }
Func *smooth_inv_(Func *input, double edge0, double edge1) { return smooth_inv(input, const_(edge0), const_(edge1)); }

Func *rounded_env(Func *edge0, Func *edge1, Func *edge2, Func *edge3) { return mul(smooth_env(edge0, edge1), smooth_inv_env(edge2, edge3)); }
Func *rounded_env_(double edge0, double edge1, double edge2, double edge3) { return rounded_env(const_(edge0), const_(edge1), const_(edge2), const_(edge3)); }
Func *rounded(Func *input, Func *edge0, Func *edge1, Func *edge2, Func *edge3) { return mul(input, rounded_env(edge0, edge1, edge2, edge3)); }
Func *rounded_(Func *input, double edge0, double edge1, double edge2, double edge3) { return rounded(input, const_(edge0), const_(edge1), const_(edge2), const_(edge3)); }

Func *adsr_env(Func *attack, Func *decay, Func *sustain, Func *release, Func *duration) { return adsr_op(timer(), attack, decay, sustain, release, duration); }
Func *adsr_env_(double attack, double decay, double sustain, double release, double duration) { return adsr_env(const_(attack), const_(decay), const_(sustain), const_(release), const_(duration)); }
Func *adsr(Func *input, Func *attack, Func *decay, Func *sustain, Func *release, Func *duration) { return mul(input, adsr_env(attack, decay, sustain, release, duration)); }
Func *adsr_(Func *input, double attack, double decay, double sustain, double release, double duration) { return adsr(input, const_(attack), const_(decay), const_(sustain), const_(release), const_(duration)); }

#endif // CSYNTH_ENVELOPES_H
