<img src="logo.jpg" width="25%" height="25%" align="right" alt="CSynth logo">

# CSynth

*A simple synth in C.*

Made by someone who knows nothing about synths.

## Usage

Play examples with PortAudio:

    ./play.sh

Generate examples to WAV file (replace `player` with wav player):

    ./write.sh && player output/run.wav

## How it works

To create music in CSynth, we nest basic (mathematical) functions into sounds,
instruments, and compositions.

Let's start simple. To play a 440 Hz sine wave for two seconds, run:

    play(sine(A4), 2);

The `A4` is 440, `sine` generates a sine wave, and `play` samples the sine
function for 2 seconds to the speakers.

Next we add a block envelope to make this into a 0.3 second note:

    func tone = sine(A4);
    func note = mul(tone, block_(0, .3));
    play(note, 2);

This adds `block`, which is value 1 for time in interval [0, 0.3] and 0
elsewhere. Then `mul` simply multiplies the tone with the envelope, resulting in
a .3 second A4 note. By default all functions take functions as arguments. The
underscore (`_`) indicates that the function takes a number.

Next we add the note in a one-second loop:

    func tone = sine(A4);
    func note = mul(tone, block_(0, .3));
    func looped = loop(note, _(1));
    play(looped, 4);

To add some reverb:

    func tone = sine(A4);
    func note = mul(tone, block_(0, .3));
    func looped = loop(note, _(1));
    func reverbed = reverb(looped, _(.4), _(.2));
    play(reverbed, 6);

## License

MIT
