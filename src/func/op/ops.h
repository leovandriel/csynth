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
#include "./mul.h"
#include "./add.h"
#include "./inv.h"
#include "./neg.h"
#include "./min.h"
#include "./max.h"
#include "./power.h"

Func *dvd(Func *a, Func *b) { return mul(a, inv(b)); }
Func *dvd_(Func *a, double b) { return dvd(a, const_(b)); }

Func *sq(Func *input) { return power(input, const_(2)); }
Func *sqr(Func *input) { return power(input, const_(0.5)); }
Func *expo(Func *input) { return power(const_(M_E), input); }

Func *clamp(Func *value, Func *min, Func *max) { return min(max(value, min), max); }
Func *clamp_(Func *value, double min, double max) { return clamp(value, const_(min), const_(max)); }

Func *sub(Func *a, Func *b) { return add(a, neg(b)); }
Func *sub_(Func *a, double b) { return sub(a, const_(b)); }

Func *ar(Func *a) { return sub_(mul_(a, 2), 1); }

Func *kr(Func *f) { return dvd_(add_(f, 1), 2); }
Func *kr_range(Func *f, Func *min, Func *max) { return add(mul(kr(f), sub(max, min)), min); }
Func *kr_range_(Func *f, double min, double max) { return add(mul(kr(f), sub(const_(max), const_(min))), const_(min)); }

#endif // CSYNTH_OPS_H
