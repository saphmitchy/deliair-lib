S=$1.cpp
O=$1.out
I=$1
A=$1_ans.txt

g++ -std=c++17 $S -Wall -O2 -o $O && ./$O < $I > $A
