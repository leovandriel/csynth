//
// comps.h - Compositions
//
#ifndef CSYNTH_COMPS_H
#define CSYNTH_COMPS_H

#include "./seq.h"

#define seq_abs(...) (seq_abs_create(FUNCS(__VA_ARGS__)))
#define seq_rel(...) (seq_rel_create(FUNCS(__VA_ARGS__)))
#define seq_seq(...) (seq_seq_create(FUNCS(__VA_ARGS__)))
#define seq_fix(...) (seq_fix_create(FUNCS(__VA_ARGS__)))
#define seq_fix_(_duration, ...) (seq_fix_create(FUNCS(const_(_duration), __VA_ARGS__)))

#endif // CSYNTH_COMPS_H
