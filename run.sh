#!/bin/bash

# run.sh

make clean
make

./ffa < data 15 16 > ffa_res
cat ffa_res | sort -k1 -k2 -n > tmp
mv tmp ffa_res

./pr > pr_res
cat pr_res | sort -k1 -k2 -n > tmp
mv tmp pr_res

head ffa_res
head pr_res