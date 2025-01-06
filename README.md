<img src="logo.jpg" width="25%" height="25%" align="right" alt="CSynth logo">

# CSynth

_A simple synth in C._

## Usage

To get started, check out the [examples](examples) folder. Each C file is
executable, e.g. to run `beep.c`:

```shell
./examples/demo/beep.c
```

This requires GCC (or clang) and [PortAudio](https://www.portaudio.com/)
binaries to be installed. You can also use CSynth without PortAudio by replacing
`play(..)` with `write_mono(..)`, which writes to a WAV file:

```shell
./examples/demo/beep_wav.c
play output/beep.wav
```

Next, emulate a basic keyboard using the bottom row (Z, X, C, ..):

```shell
./examples/demo/keyboard_synth.c
```

Or, if you have a MIDI keyboard:

```shell
./examples/demo/midi_synth.c
```

## Tutorial

To make music in CSynth, you can combine basic (mathematical) functions to
create sounds, instruments, and compositions.

Let's create a single note with reverb. Start by writing a minimal C program
that plays a 440 Hz sine wave:

```c
#include "./src/func/all.h"
#include "./src/io/player.h"

int main(void)
{
    return play(sine(A4));
}
```

Now run with (and stop by pressing Esc):

```shell
./examples/tutorial.c
```

Taking a closer look, there are three pieces here: the `A4` constant represents
440 Hz, `sine` generates a sine wave at that frequency, and `play` samples the
sine function to your speakers.

To turn the continuous tone into a 0.3 second note, add a rectangular envelope:

```c
    func tone = sine(A4);
    func note = rect_(0, .3, tone);
    play(note);
```

This adds `rect`, which multiplies `tone` by 1 during the interval [0, 0.3] and
0 elsewhere, resulting in a 0.3 second A4 note. We also use `func`, which
indicates a function variable `tone`, allowing us split things across two lines.

Notice the underscore `_`. By default, all functions take other functions as
arguments. By appending `_` to the name, you can pass in a number instead.

Next, place the note in a 1.5 second loop:

```c
    func tone = sine(A4);
    func note = rect_(0, .3, tone);
    func looped = loop_(1.5, note);
    play(looped);
```

Finally, add reverb (interval 0.4s, decay 0.2):

```c
    func tone = sine(A4);
    func note = rect_(0, .3, tone);
    func looped = loop_(1.5, note);
    func revved = reverb_(.4, .2, looped);
    play(revved);
```

Or, to make it more compact:

```c
    play(reverb_(.4,.2,loop_(1.5,rect_(0,.3,sine(A4)))));
```

This should sound like
[tutorial.mp3](https://github.com/leovandriel/csynth/raw/main/examples/tutorial.mp3).

To see more of what you can do with CSynth, take a look in
[examples/demo](examples/demo). To learn more about available functions, take a
look in [src/func](src/func) and [examples/func](examples/func). 

If you run into audio issues, run the following to get an overview of all audio
devices:

```shell
./utils/inspect_audio.c
```


## Functions

Functions are the building blocks of CSynth. They can be combined freely,
including nesting of function in unconventional ways. The tutorial started with
`play(sine(A4))`, but you can also:

```c
    play(sine(mul(A4, sine_(1))));
```

Or even:

```c
    play(sine(mul(A4, sine(sine(sine_(1))))));
```

Here, there is no distinction between audio and control (AR vs KR). There are a
few helper functions, like [ar and kr](src/func/op/ops.h) that scale the input
to respective domains:

```c
    play(sine(kr_scale(A4, sine_(1))));
```

The [sine](src/func/gen/sine.h) function has the `_` suffix to allow the
argument to be a number instead of a function. Some function take multiple
arguments in which case you may want to mix functions and numbers. This is done
by wrapping the number in `_(..)`, turning it into a function with that value
(see [const](src/func/gen/const.h)). This is most often the case with functions
like [mul](src/func/op/mul.h), which can take any number of function arguments:

```c
    play(mul(sine(A4), sine_(1), _(.5)));
```

In many cases, it is helpful to check the implementation to see the available
variations of a function, including helpful short-hands. Examples for
[mul](src/func/op/mul.h):

```c
    mul_(.5, sine(A4))
    mul(_(.5), sine(A4))
    mul(_(.5), sine(A4), sine(B4))
    mul_create(3, (func[]){_(.5), sine(A4), sine(B4)})
```

The latter opens the door to programmatic building of sound. For example, to
synthesize the sound of a G chord on the guitar using
[add_create](src/func/op/add.h):

```c
    func chord[] = {G2, B2, D3, G3, B3, G4};
    func notes[6];
    for (int i = 0; i < 6; i++)
    {
        notes[i] = delay_(.1 * i, karplus_strong_(chord[i], .5));
    }
    func strum = add_create(6, notes);
    play(strum);
```

This uses the [Karplus–Strong](src/func/gen/karplus_strong.h) method for string
synthesis. To create specific sounds like that of strings, it is often necessary
to go beyond combining existing functions. The easiest way to do this is to use
[wrap](src/func/util/wrap.h), which takes a C function as input:

```c
double phone_filter(double input, void *context)
{
    return round(input * 10) / 10;
}

int main(void)
{
    return play(wrap(phone_filter, sine(A4), NULL));
}
```

This approach has its limits, and in most cases the best approach is to
implement a function using [func_create](src/core/func.h). For example, the
above can also be implemented as:

```c
double phone_filter(size_t count, Gen **args, Eval *eval, void *context)
{
    double input = gen_eval(args[0], eval);
    return round(input * 10) / 10;
}

int main(void)
{
    func tone = sine(A4);
    func phone = func_create(NULL, phone_filter, NULL, NULL, 0, NULL, FuncFlagNone, tone);
    return play(phone);
}
```

While this looks more convoluted, it does come with the full range of available
arguments and configuration. These are all explained in detail in
[func.h](src/core/func.h).

Another way to learn more about `func_create` is to look at the implementation
of basic functions like [saw](src/func/gen/saw.h) and
[lpf](src/func/filter/lpf.h). Some of the notation is slightly different from
the examples, e.g. sources use `Func *` instead of `func` and `const_()` instead
of `_()`. This is because the examples use short-hand helpers, while the source
avoids those. Other than that, there is no specific distinction and example code
can easily make its way into the function library.

## UI

While running `play`, function parameters can be controlled with the keyboard
and displayed in the terminal. This is based on an [event](src/event/event.h)
system that broadcasts keyboard input and state changes.

Keyboard input is read by [terminal](src/ui/terminal.h) and broadcasted to
gating functions. The most basic example of this is
[mute](src/func/control/mute.h), which multiplies input by 1 and 0 alternating
at every space bar press.

```c
    play(mute(' ', sine(A4)));
```

To emulate a key on a keyboard or drum pad, use the
[trigger](src/func/control/trigger.h) function, which resets to initial state on
every key press:

```c
    play(trigger(' ', decay_(.5, sine(A4))));
```

There is also [stepper](src/func/control/stepper.h) to control with the up/down
keys and [selector](src/func/control/selector.h) to switch between functions:

```c
    play(selector(' ', sine(A3), sine(A4), sine(A5)));
```

These controls can be combined to create a
[keyboard](src/func/control/keyboard.h):

```c
    play(keyboard(trigger, decay_(.5, sine(C4))));
```

Key strokes can also be recorded and replayed with
[track](src/func/control/track.h) and [replay](src/func/control/replay.h). Key
events are managed by [keyboard_event](src/event/keyboard_event.h). To exit, the
`Esc` key is directly handled by `play`.

To visualize the state of controls, basic [display](src/ui/display.h)
functionality is included for switches and numerical values.

```c
    display_keyboard(' ', "select frequency");
    return play(selector(' ', sine(A3), sine(A4), sine(A5)));
```

While most keys can be indicated by a char, some (e.g. arrow keys) require
escape codes. To see how keys map to numbers, run:

```shell
./utils/inspect_terminal.c
```

## MIDI

CSynth supports MIDI input through
[PortMidi](https://github.com/PortMidi/portmidi). This requires linking with
PortMidi binaries and using MIDI-variant of certain functions.

A basic example of this is a MIDI keyboard based on the sawtooth function:

```c
    func tone = saw(C0);
    func synth = midi_keyboard(1, tone);
    return play_midi(synth);
```

Here, `play_midi` connects to the default MIDI device and
[midi_keyboard](./src/func/control/midi_keyboard.h) listens for MIDI events on
channel `1`. Be sure to include [midi_player.h](./src/io/midi_player.h) and link
with `portmidi`.

To make the sound more interesting, let's add a
[unison](./src/func/effect/unison.h) effect, using 5 voices and 1% detune:

```c
    func tone = unison_(5, .01, saw(C0));
    func synth = midi_keyboard(1, tone);
    return play_midi(synth);
```

`Controller` events give continuous control of a function input. For example, to
add a controlled unison effect:

```c
    func range = knob_(1, 70, 0, .02);
    func tone = unison(5, range, saw(C0));
    func synth = midi_keyboard(1, tone);
    return play_midi(synth);
```

The [knob](./src/func/control/midi_value.h) function listens for controller
events on channel 1 and number 70 and maps it to a range of 0.0 and 0.02. No
more fiddling with numbers in code!

In the above example, you might need to use a different channel or control
number. To get an overview of available MIDI devices and mapping of every key,
knob, or pad, run:

```shell
./utils/inspect_midi.c
```

To learn more about how to use MIDI, take a look at the
[midi_keyboard](./examples/func/control/midi_keyboard.c) example. To see all
available controls, see [controls](./src/func/control/). To learn more about how
MIDI is implemented, see [midi.h](./src/ui/midi.h).

## I/O

Most of the examples above use [player](src/io/player.h) to sample a function to
the system audio buffer. A [player](src/io/player.h) takes care of setting up
[PortAudio](https://www.portaudio.com/), the [sampler](src/io/sampler.h), the
[terminal](src/ui/terminal.h), and it cleans things up before exiting the
program. It comes in a few variants:

```c
    play(sine(A4));
    play_duration(10, sine(A4)); // 10 seconds
    play_stereo(sine(A4), sine(B4));
    play_stereo_duration(10, sine(A4), sine(B4));
    play_channels(4, (func[]){sine(A4), sine(B4), sine(C4), sine(D4)});
```

Instead of playing the audio, we can also write things to a wav file using
[write](src/io/writer.h):

```c
    write_mono(10, "output/sine.wav", sine(A4));
    write_mono_(10, sine(A4)); // writes to output/default.wav
    write_stereo(10, "output/sine.wav", sine(A4), sine(A4));
    write_channels(10, stdout, 4, (func[]){sine(A4), sine(B4), sine(C4), sine(D4)});
```

Under the hood, `play` and `write` use [sampler](src/io/sampler.h), which
samples functions to an audio buffer. To implement a custom audio player:

```c
    Sampler *sampler = sampler_create(44100, channel_count, channels);
    for (;;) {
        sample_t buffer = ...;
        sampler_sample(sampler, sample_count, buffer);
    }
    sampler_free(sampler);
```

Lastly, functions that rely on sample data, like [wav](src/func/gen/wav.h), use
[reader](src/io/reader.h) to load WAV data.

## How it works

CSynth represents audio synthesis as a directed acyclic graph (DAG) of functions. This architecture provides flexibility and composability while keeping the core implementation minimal and easy to understand.

The function graph is built using `*_create` functions or helper functions like `sine` and `saw`. This allows for a functional programming style where the audio composition is separate from the generation. The composition can be programmed directly in C. See [func.h](src/core/func.h) for details.

Functions are organized into categories:
- [gen](src/func/gen): Generate audio samples (sine, saw, etc.)
- [op](src/func/op): Mathematical operations (add, mul, etc.) 
- [filter](src/func/filter): Audio filters (lpf, hpf, etc.)
- [effect](src/func/effect): Complex effects (delay, reverb, etc.)
- [comp](src/func/comp): Composition tools (seq, pattern, etc.)
- [control](src/func/control): Manual controls (keyboard, midi, etc.)

Once defined, the function graph can be sampled using `player` or `writer`. These handle audio device setup, sample generation, and cleanup. During sampling, the function DAG is transformed into a generator tree, allowing functions to be reused while maintaining separate state. See [gen.h](src/core/gen.h) for details.

The `sampler` orchestrates this process:
1. Creates the generator tree via `gen_create`
2. Generates samples by calling `gen_eval` on the root generator 
3. Quantizes samples to the target format
4. Maintains `EvalParam` state for pitch, tempo, sustain etc.

Generators can be reset to their initial state using `gen_reset`. This is useful for things like envelopes that need to restart on each trigger. For example, the `trigger` function resets its generator on key press to play a new note. Reset behavior is configurable per function via `FuncFlag`.

While flexible and composable, this architecture has performance implications since even simple compositions can require hundreds of generators. To manage this, CSynth uses different evaluation rates:

- `COMPUTE_RATE`: Controls when expensive computations occur
- `CONTROL_RATE`: Reduces UI overhead 
- `DISPLAY_RATE`: Reduces display update overhead

The sampler's `compute_flag` indicates when expensive computations should run based on these rates.

## Dependencies

CSynth is designed to have minimal dependencies, relying primarily on the C standard
library. The core audio synthesis engine, file I/O, and all synth functions work
without any external dependencies.

The only external dependencies are for real-time audio/MIDI device support:

- [PortAudio](https://www.portaudio.com/) for audio playback ([player.h](src/io/player.h))
- [PortMidi](https://github.com/PortMidi/portmidi) for MIDI input ([midi_player.h](src/io/midi_player.h))

These dependencies are only included in the relevant device I/O headers and examples.
The rest of the codebase remains dependency-free and can be used standalone.

## Development

Available utilities for development:

- `./test` to run all tests
- `./test <name>` to run a specific test
- `./format` to format all code
- `./lint` to lint all code
- `./leak` to check for memory leaks
- `./doc` to generate documentation
- `./utils/inspect_audio.c` to inspect audio devices
- `./utils/inspect_midi.c` to inspect MIDI devices
- `./utils/inspect_terminal.c` to inspect terminal keys

## FAQ

_Why C?_

Cross platform and embedded systems.

## License

MIT
