#!/usr/bin/env bash
PPATH=$(realpath ..)
. ../../testdata_tools/gen.sh

setup_dirs
use_solution dp_sl.cpp

compile gen_random.py
compile gen_two.py

samplegroup
limits n=20 m=20 k=10
sample 1
sample 2
sample 3
sample 4

group group1 10
limits n=1 m=1e15 k=0 strict=0
tc line-1 gen_random k=0 n=1 m=2
tc line-2 gen_random k=0 n=1 m=1000000000000000
tc line-3 gen_random k=0 n=1 m=999999999999999
tc line-4 gen_random k=0 n=1 m=999999999999998
tc line-5 gen_random k=0 n=1 m=999999999999997
tc line-6 gen_random k=0 n=1 m=999999999999996
tc line-7 gen_random k=0 n=1 m=123126371231123

group group2 10
limits n=2 m=1e5 k=0 strict=1
tc two-1 gen_random k=0 n=2 m=1
tc two-2 gen_random k=0 n=2 m=100000
tc two-3 gen_random k=0 n=2 m=99999
tc two-4 gen_random k=0 n=2 m=99998
tc two-5 gen_random k=0 n=2 m=99997

group group3 10
limits n=2 m=1e15 k=50 strict=1
include_group group2
tc twoblock-1 gen_random n=2 m=923123123123123 k=1
tc twoblock-2 gen_two mode=narrow n=2 m=923123123123122 k=40
tc twoblock-3 gen_two mode=narrow n=2 m=923123123123121 k=30
tc twoblock-4 gen_two mode=narrow n=2 m=923123123123120 k=20
tc twoblock-5 gen_two mode=wide m=123123123123123 k=50
tc twoblock-imp1 gen_random n=2 m=923123123123123 k=45

group group4 10
limits n=1e15 m=1e15 k=0 strict=0
include_group group1
include_group group2
tc empty-tall1 gen_random k=0 n=123123123123123 m=1
tc empty-tall2 gen_random k=0 n=123123123123124 m=1
tc empty-tall3 gen_random k=0 n=123123123123125 m=1
tc empty-tall4 gen_random k=0 n=123123123123126 m=1
tc empty-tall5 gen_random k=0 n=123123123123123 m=2
tc empty-tall6 gen_random k=0 n=123123123123124 m=2
tc empty-tall7 gen_random k=0 n=123123123123125 m=2
tc empty-tall8 gen_random k=0 n=123123123123126 m=2
tc empty-1 gen_random k=0 n=123123123123123 m=123123123123124
tc empty-2 gen_random k=0 n=123123123123123 m=123123123123123
tc empty-3 gen_random k=0 n=123123123123124 m=123123123123124
tc empty-4 gen_random k=0 n=123123123123124 m=123123123123123

group group5 10
limits n=1e15 m=1e15 k=50 strict=0
include_group group4
tc twoblock-imp1
tc large-1 gen_random k=50 n=123123123123123 m=123123123123124
# TODO gen_grids

group group6 10
limits n=1e15 m=1e15 k=30000 strict=0
tc twoblock-imp1
tc huge-1 gen_random k=30000 n=123123123123123 m=123123123123124
# TODO gen_grids

cleanup_programs
