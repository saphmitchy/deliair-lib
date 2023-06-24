SOURCE=$1.cpp
OUTFILE=$1.out
INPUT=$1.in
ANSWER=$1.ans

g++ $SOURCE -Wall -Wextra -O2 -o $OUTFILE && ./$OUTFILE < $INPUT > $ANSWER
