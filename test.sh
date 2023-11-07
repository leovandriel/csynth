#!/bin/bash

set -e

if [ $# -eq 0 ]; then
    pattern=".*\\.h"
fi

if [ $# -eq 1 ]; then
    pattern=".*$1.*\\.h"
fi

find ./src -regex "$pattern" -not -path "./src/example/*" -print0 | while read -d $'\0' file; do
    name=$(basename "$file" .h)
    printf "#include \".$file\"\\nint main() { test_$name(); return 0; }" > ./src/test.c
    gcc ./src/test.c -o bin/test -Wall -Wextra -lportaudio
    ./bin/test
    echo -n "."
done

rm ./src/test.c

printf "\r\e[KAll tests passed\n"
