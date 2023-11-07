#!/bin/bash

set -e

gcc src/write.c -o bin/write -Wall -Wextra -O3
./bin/write > output/run.wav
