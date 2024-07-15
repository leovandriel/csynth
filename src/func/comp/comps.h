//
// comps.h - Compositions
//
#ifndef CSYNTH_COMPS_H
#define CSYNTH_COMPS_H

#include "../gen/param.h"
#include "./pattern.h"
#include "./seq.h"

#define seq_abs(...) (seq_abs_create(ARGS(param(EvalParamTempoTick), __VA_ARGS__)))
#define seq_rel(...) (seq_rel_create(ARGS(param(EvalParamTempoTick), __VA_ARGS__)))
#define seq_seq(...) (seq_seq_create(ARGS(__VA_ARGS__)))

#define seq_fix(__duration, ...) (seq_fix_create(ARGS(dvd(param(EvalParamTempoTick), __duration), __VA_ARGS__)))
#define seq_fix_(__duration, ...) (seq_fix(const_(__duration), __VA_ARGS__))
#define seq_loop(__duration, ...) (loop(mul_(ARGS_COUNT(__VA_ARGS__), __duration), seq_fix(__duration, __VA_ARGS__)))
#define seq_loop_(__duration, ...) (seq_loop(const_(__duration), __VA_ARGS__))

Func *pattern(const char *string, Func *duration, Func *timing, Func *input) { return pattern_create(string, duration, timing, input); }
Func *pattern_(const char *string, double duration, double timing, Func *input) { return pattern(string, const_(duration), const_(timing), input); }

#endif // CSYNTH_COMPS_H
