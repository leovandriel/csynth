#!/bin/bash

set -e

gcc src/play.c -o bin/play -Wall -Wextra -O3 -lportaudio
./bin/play $1
