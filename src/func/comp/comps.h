//
// comps.h - Compositions
//
#ifndef CSYNTH_COMPS_H
#define CSYNTH_COMPS_H

#include "../gen/param.h"
#include "./seq.h"

#define seq_abs(...) (seq_abs_create(FUNCS(param(EvalParamTempoTick), __VA_ARGS__)))
#define seq_rel(...) (seq_rel_create(FUNCS(param(EvalParamTempoTick), __VA_ARGS__)))
#define seq_seq(...) (seq_seq_create(FUNCS(__VA_ARGS__)))

#define seq_fix(__duration, ...) (seq_fix_create(FUNCS(dvd(param(EvalParamTempoTick), __duration), __VA_ARGS__)))
#define seq_fix_(__duration, ...) (seq_fix(const_(__duration), __VA_ARGS__))
#define seq_loop(__duration, ...) (loop(mul_(FUNCS_COUNT(__VA_ARGS__), __duration), seq_fix(__duration, __VA_ARGS__)))
#define seq_loop_(__duration, ...) (seq_loop(const_(__duration), __VA_ARGS__))

#endif // CSYNTH_COMPS_H
