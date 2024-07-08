//
// biquad.h - A Biquad filter
//
#ifndef CSYNTH_BIQUAD_H
#define CSYNTH_BIQUAD_H

#include <math.h>

#include "../../core/func.h"
#include "../../core/gen.h"

typedef enum
{
    BiquadTypeNone = 0,
    BiquadTypeLowpass,
    BiquadTypeHighpass,
    BiquadTypeBandpass,
    BiquadTypeNotch,
    BiquadTypePeak,
    BiquadTypeLowshelf,
    BiquadTypeHighshelf,
} BiquadType;

typedef struct
{
    BiquadType type;
    double ca0, ca1, ca2, cb1, cb2;
    double lx1, lx2, ly1, ly2;
    double time;
} BiquadContext;

static double biquad_eval(__U size_t count, Gen **args, Eval *eval, void *context_)
{
    BiquadContext *context = (BiquadContext *)context_;
    double tick = gen_eval(args[0], eval);
    double qfactor = args[1] ? gen_eval(args[1], eval) : 0.0;
    double gain = args[2] ? gen_eval(args[2], eval) : 0.0;
    double input = gen_eval(args[3], eval);

    if (context->time >= 1.0)
    {
        context->time -= 1.0;

        double omega = 2 * M_PI * tick;
        double cs_ = cos(omega);
        double sn_ = sin(omega);
        double ca0 = 0, ca1 = 0, ca2 = 0, cb0 = 0, cb1 = 0, cb2 = 0;

        switch (context->type)
        {
        case BiquadTypeNone:
            return input;
        case BiquadTypeLowpass:
        {
            double alpha = sn_ / (2 * qfactor);
            ca0 = (1 - cs_) / 2;
            ca1 = 1 - cs_;
            ca2 = (1 - cs_) / 2;
            cb0 = 1 + alpha;
            cb1 = -2 * cs_;
            cb2 = 1 - alpha;
        }
        break;
        case BiquadTypeHighpass:
        {
            double alpha = sn_ / (2 * qfactor);
            ca0 = (1 + cs_) / 2;
            ca1 = -(1 + cs_);
            ca2 = (1 + cs_) / 2;
            cb0 = 1 + alpha;
            cb1 = -2 * cs_;
            cb2 = 1 - alpha;
        }
        break;
        case BiquadTypeBandpass:
        {
            double alpha = sn_ / (2 * qfactor);
            ca0 = alpha;
            ca1 = 0;
            ca2 = -alpha;
            cb0 = 1 + alpha;
            cb1 = -2 * cs_;
            cb2 = 1 - alpha;
        }
        break;
        case BiquadTypeNotch:
        {
            double alpha = sn_ / (2 * qfactor);
            ca0 = 1;
            ca1 = -2 * cs_;
            ca2 = 1;
            cb0 = 1 + alpha;
            cb1 = -2 * cs_;
            cb2 = 1 - alpha;
        }
        break;
        case BiquadTypePeak:
        {
            double alpha = sn_ / (2 * qfactor);
            ca0 = 1 + (alpha * gain);
            ca1 = -2 * cs_;
            ca2 = 1 - (alpha * gain);
            cb0 = 1 + (alpha / gain);
            cb1 = -2 * cs_;
            cb2 = 1 - (alpha / gain);
        }
        break;
        case BiquadTypeLowshelf:
        {
            double beta = sqrt(gain * 2);
            ca0 = gain * ((gain + 1) - (gain - 1) * cs_ + beta * sn_);
            ca1 = 2 * gain * ((gain - 1) - (gain + 1) * cs_);
            ca2 = gain * ((gain + 1) - (gain - 1) * cs_ - beta * sn_);
            cb0 = (gain + 1) + (gain - 1) * cs_ + beta * sn_;
            cb1 = -2 * ((gain - 1) + (gain + 1) * cs_);
            cb2 = (gain + 1) + (gain - 1) * cs_ - beta * sn_;
        }
        break;
        case BiquadTypeHighshelf:
        {
            double beta = sqrt(gain * 2);
            ca0 = gain * ((gain + 1) + (gain - 1) * cs_ + beta * sn_);
            ca1 = -2 * gain * ((gain - 1) + (gain + 1) * cs_);
            ca2 = gain * ((gain + 1) + (gain - 1) * cs_ - beta * sn_);
            cb0 = (gain + 1) - (gain - 1) * cs_ + beta * sn_;
            cb1 = 2 * ((gain - 1) - (gain + 1) * cs_);
            cb2 = (gain + 1) - (gain - 1) * cs_ - beta * sn_;
        }
        break;
        }

        context->ca0 = ca0 / cb0;
        context->ca1 = ca1 / cb0;
        context->ca2 = ca2 / cb0;
        context->cb1 = cb1 / cb0;
        context->cb2 = cb2 / cb0;
    }

    double output = context->ca0 * input +
                    context->ca1 * context->lx1 +
                    context->ca2 * context->lx2 -
                    context->cb1 * context->ly1 -
                    context->cb2 * context->ly2;
    context->lx2 = context->lx1;
    context->lx1 = input;
    context->ly2 = context->ly1;
    context->ly1 = output;
    context->time += eval->tick[EvalTickCompute];

    return output;
}

Func *biquad_create(BiquadType type, Func *tick, Func *qfactor, Func *gain, Func *input)
{
    BiquadContext initial = {
        .type = type,
        .lx1 = 0,
        .lx2 = 0,
        .ly1 = 0,
        .ly2 = 0,
        .time = 1.0,
    };
    return func_create(NULL, biquad_eval, NULL, sizeof(BiquadContext), &initial, FuncFlagNone, FUNCS(tick, qfactor, gain, input));
}

#endif // CSYNTH_BIQUAD_H
