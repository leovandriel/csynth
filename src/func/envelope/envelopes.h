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
#include "../op/inv.h"
#include "../op/neg.h"
#include "../op/ops.h"
#include "./smooth.h"
#include "./step.h"

Func *decay_env(Func *factor) { return expo(dvd(neg(timer()), factor)); }
Func *decay_env_(double factor) { return decay_env(const_(factor)); }
Func *decay(Func *f, Func *factor) { return mul(f, decay_env(factor)); }
Func *decay_(Func *f, double factor) { return decay(f, const_(factor)); }

Func *decay_from_env(Func *from, Func *to, Func *factor) { return add(mul(decay_env(factor), sub(from, to)), to); }
Func *decay_from_env_(double from, double to, double factor) { return decay_from_env(const_(from), const_(to), const_(factor)); }
Func *decay_from(Func *f, Func *from, Func *to, Func *factor) { return mul(f, decay_from_env(from, to, factor)); }
Func *decay_from_(Func *f, double from, double to, double factor) { return decay_from(f, const_(from), const_(to), const_(factor)); }

Func *linear_env(Func *a, Func *b, Func *t) { return add(mul(timer(), dvd(sub(b, a), t)), a); }
Func *linear_env_(double a, double b, double t) { return linear_env(const_(a), const_(b), const_(t)); }
Func *linear(Func *f, Func *a, Func *b, Func *t) { return mul(f, linear_env(a, b, t)); }
Func *linear_(Func *f, double a, double b, double t) { return linear(f, const_(a), const_(b), const_(t)); }

Func *step_inv_env(Func *edge) { return sub(ONE, step_env(edge)); }
Func *step_inv_env_(double edge) { return step_inv_env(const_(edge)); }
Func *step_inv(Func *f, Func *edge) { return mul(f, step_inv_env(edge)); }
Func *step_inv_(Func *f, double edge) { return step_inv(f, const_(edge)); }

Func *block_env(Func *edge0, Func *edge1) { return mul(step_env(edge0), step_inv_env(edge1)); }
Func *block_env_(double edge0, double edge1) { return block_env(const_(edge0), const_(edge1)); }
Func *block(Func *f, Func *edge0, Func *edge1) { return mul(f, block_env(edge0, edge1)); }
Func *block_(Func *f, double edge0, double edge1) { return block(f, const_(edge0), const_(edge1)); }

Func *smooth_inv_env(Func *edge0, Func *edge1) { return sub(ONE, smooth_env(edge0, edge1)); }
Func *smooth_inv_env_(double edge0, double edge1) { return smooth_inv_env(const_(edge0), const_(edge1)); }
Func *smooth_inv(Func *f, Func *edge0, Func *edge1) { return mul(f, smooth_inv_env(edge0, edge1)); }
Func *smooth_inv_(Func *f, double edge0, double edge1) { return smooth_inv(f, const_(edge0), const_(edge1)); }

Func *hump_env(Func *edge0, Func *edge1, Func *edge2, Func *edge3) { return mul(smooth_env(edge0, edge1), smooth_inv_env(edge2, edge3)); }
Func *hump_env_(double edge0, double edge1, double edge2, double edge3) { return hump_env(const_(edge0), const_(edge1), const_(edge2), const_(edge3)); }
Func *hump(Func *f, Func *edge0, Func *edge1, Func *edge2, Func *edge3) { return mul(f, hump_env(edge0, edge1, edge2, edge3)); }
Func *hump_(Func *f, double edge0, double edge1, double edge2, double edge3) { return hump(f, const_(edge0), const_(edge1), const_(edge2), const_(edge3)); }

#endif // CSYNTH_ENVELOPES_H
