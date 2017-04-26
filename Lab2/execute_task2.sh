#!/usr/bin/env bash
set -e

EXECUTABLE="task2"
C_SOURCE="task2.c"

gcc "$C_SOURCE" -o "$EXECUTABLE"
./"$EXECUTABLE"

set +e