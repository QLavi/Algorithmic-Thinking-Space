DIR=$1
PROG_NAME=$2
echo "[INFO] compiling and executing ..."
echo ""
set +x
gcc -g -Wall -Werror -Wextra "$DIR/$PROG_NAME.c" && ./a.out < "$DIR/input.txt"
set -x