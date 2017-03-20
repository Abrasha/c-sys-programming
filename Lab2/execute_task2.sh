#!/usr/bin/env bash
set -e

EXECUTABLE="task2"
C_SOURCE="task2.c"
LABEL="debug-label"

gcc "$C_SOURCE" -o "$EXECUTABLE" -ggdb -ansi -pedantic -Wall -Werror
./"$EXECUTABLE" "$LABEL"

set +e