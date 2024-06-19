//usr/bin/gcc "$0" -o bin/midi_synth -Wall -Wextra -O3 -lm -lportaudio -lportmidi && ./bin/midi_synth "$@"; exit $?
#include "../../src/func/all.h"
#include "../../src/io/midi_player.h"

func note(func frequency)
{
    return unison(frequency, saw, 5, 0.01);
}

int main()
{
    func lpf_knob = knob_exp_(70, 0, 40000, 1);
    func hpf_knob = knob_exp_(71, 0, 1, 40000);
    func distortion_knob = knob_(72, 0, 0, 10);
    func post_gain = knob_(77, 0, 1, 5);
    func reverb_time = knob_(75, 0, 0, .2);
    func reverb_decay = knob_(76, 0, .1, .9);
    func keys = midi_keyboard(0, key, note, C0);
    func keys_filtered = mul(reverb(lpf(hpf(distortion(keys, distortion_knob), hpf_knob), lpf_knob), reverb_time, reverb_decay), post_gain);
    func drums = add(pad(40, 9, snare()), pad(41, 9, bdrum()), pad(42, 9, hihat()));
    return play_midi(add(mul_(keys_filtered, .2), drums));
}
