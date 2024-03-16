<img src="logo.jpg" width="25%" height="25%" align="right" alt="CSynth logo">

# CSynth

*A simple synth in C.*

## Usage

Play examples with PortAudio:

    ./play.c

Samples examples into a WAV file (replace `player` with wav player):

    ./write.c && player output/example.wav

## PortAudio

PortAudio is only needed for running `play.c`. To install PortAudio on Mac:
`brew install portaudio`.

## Example

To create music in CSynth, we nest basic (mathematical) functions into sounds,
instruments, and compositions.

Let's start simple. To play a 440 Hz sine wave for two seconds, run:

```c
play(sine(A4), 2);
```

The `A4` is 440, `sine` generates a sine wave at the given frequency, and `play`
samples the sine function for 2 seconds to the speakers.

Next, we add a block envelope to make this into a 0.3 second note:

```c
func tone = sine(A4);
func note = mul(tone, block_(0, .3));
play(note, 2);
```

This adds `block`, which is value 1 for time in interval [0, 0.3] and 0
elsewhere. Then `mul` simply multiplies the tone with the envelope, resulting in
a .3 second A4 note. By default, all functions take functions as arguments. The
underscore `_` indicates that the function takes a number.

Next, we add the note in a 1.5 second loop:

```c
func tone = sine(A4);
func note = mul(tone, block_(0, .3));
func looped = loop_(note, 1.5);
play(looped, 4);
```

Finally, we add reverb (interval .4s, decay .2) and scale the note to prevent
clipping:

```c
func tone = sine(A4);
func note = mul(tone, block_(0, .3), _(.5));
func looped = loop_(note, 1.5);
func revved = reverb_(looped, .4, .2);
play(revved, 6);
```

You can hear the result in
[example.mp3](https://github.com/leovandriel/csynth/raw/main/output/example.mp3)
or by running:

    ./play.c example

To see more of what you can do with CSynth, take a look at the
[example](src/example) folder.

To learn more about available functions, take a look at the [func](src/func)
folder.

## How it works

The `func` is the primary building block. Almost all functions take another
functions as input. These inputs can represent a signal that they transform
(e.g. `input` in `loop()`) or a parameter that is used for generating a signal
(e.g. `frequency` in `sine()`). To CSynth there is no difference.

By nesting functions, we can create a acyclic graph of functions. When this is
fed into the `player` or `writer`, we traverse the graph and turn it into a tree
of generators (`Gen`), together with a sample rate (as a time `delta`). The root
generator then recursively samples the tree.

This creation of generators allows functions to be reused during composition,
i.e. to be a acyclic graph instead of a strict tree.

All of the above logic is defined in [func.h](src/core/func.h).

## Development

To run tests:

    ./test.sh

Example run specific test:

    ./test.sh sine

## FAQ

*Why C?*

Because it didn't seem like a good idea.

## License

MIT
