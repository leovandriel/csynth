#!/bin/bash

set -e

gcc src/play.c -o bin/play -Wall -Wextra -O3 -lm -lportaudio
./bin/play $1
