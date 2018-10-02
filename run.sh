#!/bin/bash

# run.sh

make clean
make

./bin/ffa < data 15 16 > ffa_res
# cat ffa_res | sort 

./bin/pr > pr_res