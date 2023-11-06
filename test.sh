#!/bin/bash

set -e

for filename in ./src/funcs/*.h; do
    name=$(basename "$filename" .h)
    printf "#include \".$filename\"\\nint main() { test_$name(); return 0; }" > ./src/test.c
    gcc ./src/test.c -o bin/test -Wall -Wextra
    ./bin/test
done

rm ./src/test.c

echo "All tests passed"
