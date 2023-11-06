#!/bin/bash

set -e

gcc src/play.c -o bin/run -Wall -Wextra -O3 -lportaudio
./bin/run
