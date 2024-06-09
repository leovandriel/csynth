<img src="logo.jpg" width="25%" height="25%" align="right" alt="CSynth logo">

# CSynth

_A simple synth in C._

## Usage

To get started, check out the [examples](examples) folder. Each C file is
executable, e.g. to run `beep.c`, simply run:

    ./examples/demo/beep.c

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

    ./examples/tutorial.c

Taking a closer look, there are three pieces here: the `A4` constant represents
440 Hz, `sine` generates a sine wave at that frequency, and `play` samples the
sine function to your speakers.

This probably sounded quite loud. Let's bring it down a little to save our ears:

```c
    func tone = sine(A4);
    play(mul_(tone, .5));
```

Here we introduce `mul`, which multiplies both inputs. By multiplying by 0.5,
the volume becomes less. This also adds `func`, which indicates a function
variable `tone`, allowing us split things across two lines.

Note the underscore `_`. By default, all functions take other functions as
arguments. By appending `_`, you can pass in numbers instead.

Next, add a block envelope to turn this into a 0.3 second note:

```c
    func tone = sine(A4);
    func note = block_(tone, 0, .3);
    play(mul_(note, .5));
```

This adds `block`, which multiplies tone by 1 during the interval [0, 0.3] and 0
elsewhere, resulting in a 0.3 second A4 note.

Next, add the note in a 1.5 second loop:

```c
    func tone = sine(A4);
    func note = block_(tone, 0, .3);
    func looped = loop_(note, 1.5);
    play(mul_(looped, .5));
```

Finally, add reverb (interval .4s, decay .2):

```c
    func tone = sine(A4);
    func note = block_(tone, 0, .3);
    func looped = loop_(note, 1.5);
    func revved = reverb_(looped, .4, .2);
    play(mul_(revved, .5));
```

To listen to the result:
[tutorial.mp3](https://github.com/leovandriel/csynth/raw/main/examples/tutorial.mp3)

To see more of what you can do with CSynth, take a look in
[examples/demo](examples/demo).

To learn more about available functions, take a look in [src/func](src/func).

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

    ./test

Example run specific test:

    ./test sine

## FAQ

_Why C?_

Because it didn't seem like a good idea at the time.

## License

MIT
