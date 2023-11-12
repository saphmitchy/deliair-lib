#!bin/bash
g++ -std=gnu++2a -Wall -O2 $1.cpp

for file in $1/*.in
do
    echo $file
    ./a.out < $file
done