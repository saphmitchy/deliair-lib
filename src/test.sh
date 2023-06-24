SOURCE=$1.cpp
OUTFILE=$1.out
TEST=test.txt

g++ $SOURCE -Wall -Wextra -g -O0 -fsanitize=undefined,address -o $OUTFILE && ./$OUTFILE < $TEST
