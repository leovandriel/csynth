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

Func *decay(Func *factor) { return expo(dvd(neg(timer()), factor)); }
Func *decay_(double factor) { return decay(const_(factor)); }
Func *decay_from(Func *from, Func *to, Func *factor) { return add(mul(decay(factor), sub(from, to)), to); }
Func *decay_from_(double from, double to, double factor) { return decay_from(const_(from), const_(to), const_(factor)); }

Func *linear(Func *a, Func *b, Func *t) { return add(mul(timer(), dvd(sub(b, a), t)), a); }
Func *linear_(double a, double b, double t) { return linear(const_(a), const_(b), const_(t)); }

Func *step_inv(Func *edge) { return sub(ONE, step(edge)); }
Func *step_inv_(double edge) { return step_inv(const_(edge)); }

Func *block(Func *edge0, Func *edge1) { return mul(step(edge0), step_inv(edge1)); }
Func *block_(double edge0, double edge1) { return block(const_(edge0), const_(edge1)); }

Func *smooth_inv(Func *edge0, Func *edge1) { return sub(ONE, smooth(edge0, edge1)); }
Func *smooth_inv_(double edge0, double edge1) { return smooth_inv(const_(edge0), const_(edge1)); }

Func *hump(Func *edge0, Func *edge1, Func *edge2, Func *edge3) { return mul(smooth(edge0, edge1), smooth_inv(edge2, edge3)); }
Func *hump_(double edge0, double edge1, double edge2, double edge3) { return hump(const_(edge0), const_(edge1), const_(edge2), const_(edge3)); }

#endif // CSYNTH_ENVELOPES_H
