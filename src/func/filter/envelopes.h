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
Func *decay(Func *f, Func *factor) { return mul(f, decay_env(factor)); }
Func *decay_(Func *f, double factor) { return decay(f, const_(factor)); }

Func *decay_from_env(Func *from, Func *to, Func *factor) { return add(mul(decay_env(factor), sub(from, to)), to); }
Func *decay_from_env_(double from, double to, double factor) { return decay_from_env(const_(from), const_(to), const_(factor)); }
Func *decay_from(Func *f, Func *from, Func *to, Func *factor) { return mul(f, decay_from_env(from, to, factor)); }
Func *decay_from_(Func *f, double from, double to, double factor) { return decay_from(f, const_(from), const_(to), const_(factor)); }

Func *linear_env(Func *a, Func *b, Func *t) { return linear_op(timer(), a, b, t); }
Func *linear_env_(double a, double b, double t) { return linear_env(const_(a), const_(b), const_(t)); }
Func *linear(Func *f, Func *a, Func *b, Func *t) { return mul(f, linear_env(a, b, t)); }
Func *linear_(Func *f, double a, double b, double t) { return linear(f, const_(a), const_(b), const_(t)); }

Func *step_env(Func *edge) { return step_op(timer(), edge); }
Func *step_env_(double edge) { return step_env(const_(edge)); }
Func *step(Func *f, Func *edge) { return mul(f, step_env(edge)); }
Func *step_(Func *f, double edge) { return step(f, const_(edge)); }

Func *step_inv_env(Func *edge) { return sub(ONE, step_env(edge)); }
Func *step_inv_env_(double edge) { return step_inv_env(const_(edge)); }
Func *step_inv(Func *f, Func *edge) { return mul(f, step_inv_env(edge)); }
Func *step_inv_(Func *f, double edge) { return step_inv(f, const_(edge)); }

Func *rect_env(Func *edge0, Func *edge1) { return mul(step_env(edge0), step_inv_env(edge1)); }
Func *rect_env_(double edge0, double edge1) { return rect_env(const_(edge0), const_(edge1)); }
Func *rect(Func *f, Func *edge0, Func *edge1) { return mul(f, rect_env(edge0, edge1)); }
Func *rect_(Func *f, double edge0, double edge1) { return rect(f, const_(edge0), const_(edge1)); }

Func *smooth_env(Func *edge0, Func *edge1) { return smooth_op(timer(), edge0, edge1); }
Func *smooth_env_(double edge0, double edge1) { return smooth_env(const_(edge0), const_(edge1)); }
Func *smooth(Func *f, Func *edge0, Func *edge1) { return mul(f, smooth_env(edge0, edge1)); }
Func *smooth_(Func *f, double edge0, double edge1) { return smooth(f, const_(edge0), const_(edge1)); }

Func *smooth_inv_env(Func *edge0, Func *edge1) { return sub(ONE, smooth_env(edge0, edge1)); }
Func *smooth_inv_env_(double edge0, double edge1) { return smooth_inv_env(const_(edge0), const_(edge1)); }
Func *smooth_inv(Func *f, Func *edge0, Func *edge1) { return mul(f, smooth_inv_env(edge0, edge1)); }
Func *smooth_inv_(Func *f, double edge0, double edge1) { return smooth_inv(f, const_(edge0), const_(edge1)); }

Func *rounded_env(Func *edge0, Func *edge1, Func *edge2, Func *edge3) { return mul(smooth_env(edge0, edge1), smooth_inv_env(edge2, edge3)); }
Func *rounded_env_(double edge0, double edge1, double edge2, double edge3) { return rounded_env(const_(edge0), const_(edge1), const_(edge2), const_(edge3)); }
Func *rounded(Func *f, Func *edge0, Func *edge1, Func *edge2, Func *edge3) { return mul(f, rounded_env(edge0, edge1, edge2, edge3)); }
Func *rounded_(Func *f, double edge0, double edge1, double edge2, double edge3) { return rounded(f, const_(edge0), const_(edge1), const_(edge2), const_(edge3)); }

Func *adsr_env(Func *attack, Func *decay, Func *sustain, Func *release, Func *duration) { return adsr_op(timer(), attack, decay, sustain, release, duration); }
Func *adsr_env_(double attack, double decay, double sustain, double release, double duration) { return adsr_env(const_(attack), const_(decay), const_(sustain), const_(release), const_(duration)); }
Func *adsr(Func *f, Func *attack, Func *decay, Func *sustain, Func *release, Func *duration) { return mul(f, adsr_env(attack, decay, sustain, release, duration)); }
Func *adsr_(Func *f, double attack, double decay, double sustain, double release, double duration) { return adsr(f, const_(attack), const_(decay), const_(sustain), const_(release), const_(duration)); }

#endif // CSYNTH_ENVELOPES_H
