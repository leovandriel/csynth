<img src="logo.jpg" width="25%" height="25%" align="right" alt="CSynth logo">

# CSynth

_A simple synth in C._

## Usage

To get started, check out the [examples](examples) folder. Each C file is
executable, e.g. to run `beep.c`, simply run:

```shell
./examples/demo/beep.c
```

This requires GCC (or clang) and [PortAudio](https://www.portaudio.com/)
binaries to be installed. You can also use CSynth without PortAudio; just
replace `play(..)` with `write(..)` to write to a WAV file.

## Tutorial

To make music in CSynth, combine basic (mathematical) functions to create
sounds, instruments, and compositions.

Let's create a single note with reverb. Start by writing a minimal C program
that plays a 440 Hz sine wave:

```c
#include "./src/func/all.h"
#include "./src/io/player.h"

int main()
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

That probably sounded quite loud. Let's bring it down a little to save our ears:

```c
    func tone = sine(A4);
    play(mul_(tone, .5));
```

Here we introduce `mul`, which multiplies both arguments together. By
multiplying by 0.5, the volume becomes less. This also adds `func`, which
indicates a function variable `tone`, allowing us split things across two lines.

Note the underscore `_`. By default, all functions take other functions as
arguments. By appending `_`, you can pass in a fixed value instead.

Next, add a rectangular envelope to turn this into a 0.3 second note:

```c
    func tone = sine(A4);
    func note = rect_(tone, 0, .3);
    play(mul_(note, .5));
```

This adds `rect`, which multiplies tone by 1 during the interval [0, 0.3] and 0
elsewhere, resulting in a 0.3 second A4 note.

Next, add the note in a 1.5 second loop:

```c
    func tone = sine(A4);
    func note = rect_(tone, 0, .3);
    func looped = loop_(note, 1.5);
    play(mul_(looped, .5));
```

Finally, add reverb (interval .4s, decay .2):

```c
    func tone = sine(A4);
    func note = rect_(tone, 0, .3);
    func looped = loop_(note, 1.5);
    func revved = reverb_(looped, .4, .2);
    play(mul_(revved, .5));
```

Or, to make it more compact:

```c
    play(mul_(reverb_(loop_(rect_(sine(A4),0,.3),1.5),.4,.2),.5));
```

To listen to the result:
[tutorial.mp3](https://github.com/leovandriel/csynth/raw/main/examples/tutorial.mp3)

To see more of what you can do with CSynth, take a look in
[examples/demo](examples/demo).

To learn more about available functions, take a look in [src/func](src/func) and
[examples/func](examples/func).

## Functions

Functions are the building blocks of CSynth. They can be combined freely,
including nesting of function in unconventional ways. The tutorial started with
`play(sine(A4))`, but you can also:

```c
    play(sine(sine(A4)));
```

Or even (although it will be hard to hear):

```c
    play(sine(sine(sine(A4))));
```

There is no distinction between audio and control (e.g. AR vs KR), but there are
a few helper functions, like [ar and kr](src/func/op/ops.h) that scale the input
to respective domains:

```c
    play(sine(kr_scale(sine_(2), A4)));
```

Here [sine](src/func/gen/sine.h) has the `_` suffix, to allow the argument to be
a fixed value, instead of a function. Some function take multiple arguments in
which case you may want to mix functions and values. This is done by wrapping
the value in `_(..)`, turning it into a function with that value (see
[const](src/func/gen/const.h)). This is most often the case with functions like
[mul](src/func/op/mul.h) which can take any number of function arguments:

```c
    play(mul(sine(A4), sine_(1), _(.5)));
```

In many cases, it is helpful to check the implementation to see the available
variations of a function, including helpful short-hands. Examples for
[mul](src/func/op/mul.h):

```c
    mul_(sine(A4), .5)
    mul(sine(A4), _(.5))
    mul(sine(A4), sine(B4), _(.5))
    mul_array(4, (Func *[]){sine(A4), sine(B4), sine(C4), _(.5)})
```

The latter opens the door to programmatic building of sound. For example, to
synthesize the sound of a G chord on the guitar using
[add_array](src/func/op/add.h):

```c
    func chord[] = {G2, B2, D3, G3, B3, G4};
    func notes[6];
    for (int i = 0; i < 6; i++)
    {
        notes[i] = delay_(karplus_strong_(chord[i], .1), .1 * i);
    }
    play(mul_(add_array(6, notes), .5));
```

This uses the [Karplus–Strong](src/func/gen/karplus_strong.h) method for string
synthesis. To create specific sounds like that of strings, it is often necessary
to go beyond combining existing functions. The easiest way to do this is to use
[wrap](src/func/util/wrap.h), which takes a C function as input:

```c
double step_filter(double input, double delta)
{
    return round(input * 10) / 10;
}

int main()
{
    return play(wrap(sine(A4), step_filter));
}
```

This approach has its limits, and in most cases the best approach is to
implement a function from scratch using [func_create](src/core/func.h). For
example, the above can also be implemented as:

```c
double step_filter(int count, Gen **args, double delta, void *context)
{
    return round(gen_eval(args[0]) * 10) / 10;
}

int main()
{
    return play(func_create(NULL, step_filter, NULL, 0, NULL, FUNC_FLAG_DEFAULT, 1, sine(A4)));
}
```

While this looks a bit more convoluted, it does come with the full range of
available arguments and configuration. These are all explained in detail in
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
[unmute](src/func/contro/unmute), which multiplies input by 0 and 1 alternating at
every space bar press.

```c
    play(unmute(' ', sine(A4)));
```

To emulate a key on a keyboard or drum pad, use the
[trigger](src/func/control/trigger.h) function, which resets to initial state on
every key press:

```c
    play(trigger(' ', decay_(sine(A4), .1)));
```

There is also [knob](src/func/control/knob.h) to modulate a value and
[selector](src/func/control/selector.h) to switch between functions:

```c
    play(selector(' ', sine(A4), sine(A5), sine(A6)));
```

These controls can be combined to create a
[keyboard](src/func/control/controls.h):

```c
func note(func frequency)
{
    return decay_(sine(frequency), .1);
}

int main()
{
    return play(keyboard(trigger, note, C4));
}
```

Keyboard strokes can also be recorded and replay with
[track](src/func/control/track.h) and [replay](src/func/control/replay.h). Key
events are managed by [key_event](src/event/key_event.h). Two keys are directly
handled by `play`: `Tab` to pause, and `Esc` to exit.

To visualize the state of controls, basic [display](src/ui/display.h)
functionality is included for switches and numerical values. 

```c
    display(' ', "select frequency");
    return play(selector(' ', sine(A4), sine(A5), sine(A6)));
```

## I/O

Most of the examples above use [play](src/io/player.h) to sample a function to
the system audio buffer. [play](src/io/player.h) takes care of setting up
[PortAudio](https://www.portaudio.com/), the [sampler](src/io/sampler.h), the
[terminal](src/ui/terminal.h), and it cleans things up before exiting the
program. It comes in a few variants:

```c
    play(sine(A4));
    play_(sine(A4), 10); // 10 seconds
    play_stereo(sine(A4), sine(B4));
    play_stereo_duration(sine(A4), sine(B4), 10);
    player_play_channels(4, (Func *[]){sine(A4), sine(B4), sine(C4), sine(D4)}, 10);
```

Instead of playing the audio, we can also write things to a wav file using
[write](src/io/writer.h):

```c
    write(sine(A4), 10, "output/sine.wav");
    write_(sine(A4), 10); // writes to output/default.wav
    write_stereo(sine(A4), sine(A4), 10, "output/sine.wav");
    writer_write_channels(2, (Func *[]){sine(A4), sine(B4)}, 10, stdout);
```

Under the hood, `play` and `write` use [sampler](src/io/sampler.h). This makes
it easy to implement a custom audio player:

```c
    Sampler *sampler = sampler_create(channel_count, channels);
    for (;;) {
        sample_t buffer = ...;
        sampler_sample(sampler, sample_count, buffer);
    }
    sampler_free(sampler);
```

Lastly, functions that rely on sample data, like [wav](src/func/gen/wav.h), use
[reader](src/io/reader.h) to load WAV data.

## How it works

The `func` is the primary building block, representing a function that outputs a
value over time. Almost all functions take another functions as input, allowing
the creation of complex sounds from primitives like sawtooth waves and
envelopes. These inputs can represent a signal that they transform (e.g. `input`
in `loop()`) or a parameter that is used for generating a signal (e.g.
`frequency` in `saw()`).

By nesting functions, you can create a directed acyclic graph of functions. When
this is fed into the `player` or `writer`, the graph is traversed and
transformed into a tree of generators, together with a sample rate (as a time
`delta`). The root generator then recursively samples the tree.

All of the above logic is defined in [func.h](src/core/func.h) and
[gen.h](src/core/gen.h).

## Development

To run tests:

```shell
./test
```

Example run specific test:

```shell
./test sine
```

## FAQ

_Why C?_

Because it didn't seem like a good idea at the time.

## License

MIT
