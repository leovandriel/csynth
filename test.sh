#!/bin/bash

set -e

for filename in ./src/funcs/*.h; do
    name=$(basename "$filename" .h)
    printf "#include \".$filename\"\\nint main() { test_$name(); return 0; }" > ./bin/test.c
    gcc ./bin/test.c -o bin/test -Wall -Wextra
    ./bin/test
done

echo "All tests passed"
