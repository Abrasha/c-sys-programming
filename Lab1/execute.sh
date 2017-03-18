set -e

EXECUTABLE="out"

gcc "$1" -o "$EXECUTABLE" -ggdb -ansi -pedantic -Wall -Werror
./"$EXECUTABLE"

set +e