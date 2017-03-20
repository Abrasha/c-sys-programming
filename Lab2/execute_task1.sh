#!/usr/bin/env bash
set -e

EXECUTABLE="task1"
C_SOURCE="task1.c"

gcc "$C_SOURCE" -o "$EXECUTABLE" -ggdb -ansi -pedantic -Wall -Werror
./"$EXECUTABLE"

set +e