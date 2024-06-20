//usr/bin/gcc "$0" -o bin/midi_synth -Wall -Wextra -O3 -lm -lportaudio -lportmidi && ./bin/midi_synth "$@"; exit $?
#include "../../src/func/all.h"
#include "../../src/io/midi_player.h"

func note(func frequency)
{
    return unison(frequency, saw, 5, 0.01);
}

int main()
{
    func lpf_knob = knob_exp_(1, 70, 40000, 1);
    display_midi(1, 70, "lpf");
    func hpf_knob = knob_exp_(1, 71, 1, 40000);
    display_midi(1, 71, "hpf");
    func distortion_knob = knob_(1, 72, 0, 10);
    display_midi(1, 72, "distort");
    func post_gain = knob_(1, 77, 1, 5);
    display_midi(1, 77, "gain");
    func reverb_time = knob_(1, 75, 0, .2);
    display_midi(1, 75, "rev-time");
    func reverb_decay = knob_(1, 76, 0, .9);
    display_midi(1, 76, "rev-decay");
    func keys = midi_keyboard(1, key, note, C0);
    func keys_filtered = mul(reverb(lpf(hpf(distortion(keys, distortion_knob), hpf_knob), lpf_knob), reverb_time, reverb_decay), post_gain);
    func drums = add(pad(10, 40, snare()), pad(10, 41, bdrum()), pad(10, 42, hihat()));
    return play_midi(add(mul_(keys_filtered, .2), drums));
}
