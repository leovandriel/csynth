<img src="logo.jpg" width="25%" height="25%" align="right" alt="CSynth logo">

# CSynth

_A simple synth in C._

## Usage

CSynth is a header-only library. Most functionality is accessible through
`src/func/all.h`.

To get started, check out the [examples](examples) folder, e.g. by running:

    ./examples/beep.c

This requires GCC and [PortAudio](https://www.portaudio.com/) binaries to be
installed. You can also use CSynth without PortAudio; simply replace `play(..)`
with `write(..)` to write to a WAV file.

## Tutorial

To create music in CSynth, combine basic (mathematical) functions to create
sounds, instruments, and compositions. Let's create a single note with reverb.

Start by playing a 440 Hz sine wave (and stop by pressing Ctrl-C):

```c
play(sine(A4));
```

The `A4` constant represents a 440 Hz, `sine` generates a sine wave at that
frequency, and `play` samples the sine function for 2 seconds to your speakers.

Next, add a block envelope to make this into a 0.3 second note:

```c
func tone = sine(A4);
func note = mul(tone, block_(0, .3));
play(note);
```

This adds `block`, which is value 1 for time in interval [0, 0.3] and 0
elsewhere. `mul` simply multiplies the tone with the envelope, resulting in a .3
second A4 note. By default, all functions take functions as arguments. The
underscore `_` indicates that the function takes a number.

Next, add the note in a 1.5 second loop:

```c
func tone = sine(A4);
func note = mul(tone, block_(0, .3));
func looped = loop_(note, 1.5);
play(looped);
```

Finally, add reverb (interval .4s, decay .2) and scale the note to prevent
clipping:

```c
func tone = sine(A4);
func note = mul(tone, block_(0, .3), _(.5));
func looped = loop_(note, 1.5);
func revved = reverb_(looped, .4, .2);
play(revved);
```

Listen to the result in
[example.mp3](https://github.com/leovandriel/csynth/raw/main/output/example.mp3)
or by running:

    ./examples/beep.c

To see more of what you can do with CSynth, take a look at the
[examples](examples).

To learn more about available functions, take a look at the [func](src/func)
folder.

## How it works

The `func` is the primary building block, representing a function that outputs a
value over time. Almost all functions take another functions as input, allowing
the creation of complex sounds from primitives like sine waves and envelopes.
These inputs can represent a signal that they transform (e.g. `input` in
`loop()`) or a parameter that is used for generating a signal (e.g. `frequency`
in `sine()`). To CSynth there is no difference.

By nesting functions, you can create a acyclic graph of functions. When this is
fed into the `player` or `writer`, traverse the graph and turn it into a tree of
generators (`Gen`), together with a sample rate (as a time `delta`). The root
generator then recursively samples the tree.

This creation of generators allows functions to be reused during composition,
i.e. to be a acyclic graph instead of a strict tree.

All of the above logic is defined in [func.h](src/core/func.h).

## Development

To run tests:

    ./test

Example run specific test:

    ./test sine

## FAQ

_Why C?_

Because it didn't seem like a good idea.

## License

MIT
