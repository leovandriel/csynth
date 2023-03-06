Audio
=====

*Generate music with PortAudio.*

# Usage

Run:

    gcc src/run.c -o bin/run -Wall -Wextra -O3 && ./bin/run && afplay output/run.wav

If using player:
    gcc src/run.c -o bin/run -lportaudio -Wall -Wextra -O3 && ./bin/run

# License

MIT
