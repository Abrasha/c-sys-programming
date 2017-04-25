#!/usr/bin/env bash
set -e

EXECUTABLE="task1"
C_SOURCE="task1.c"

gcc "$C_SOURCE" -o "$EXECUTABLE"
./"$EXECUTABLE" &


LAST_PID=$!

for i in `seq 1 7`; do
    echo "sending signal #$i"
    kill -1 ${LAST_PID}
    sleep 1
done

cat lab3_1.log

kill ${LAST_PID}

set +e