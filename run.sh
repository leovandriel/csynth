#!/bin/bash

set -e

gcc src/run.c -o bin/run -Wall -Wextra -O3
./bin/run
