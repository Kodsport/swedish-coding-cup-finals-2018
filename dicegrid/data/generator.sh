#!/usr/bin/env bash
PPATH=$(realpath ..)
. ../../testdata_tools/gen.sh

setup_dirs
use_solution fancy_sl.cpp

compile gen_random.py
compile gen_two.py
compile gen_grids.py

samplegroup
limits n=20 m=20 k=10 strict=0
sample 1
sample 2
sample 3
sample 4

group group1 5
limits n=1 m=1e15 k=0 strict=0
tc line-1 gen_random k=0 n=1 m=2
tc line-2 gen_random k=0 n=1 m=1000000000000000
tc line-3 gen_random k=0 n=1 m=123126371231123
tc line-4 gen_random k=0 n=1 m=999999999999998
tc line-5 gen_random k=0 n=1 m=999999999999997

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

group group4 0
limits n=1e2 m=1e2 k=50 strict=0
sed -i 's#range: 0 0#range: -1 0#' secret/group4/testdata.yaml
tc testing-1 gen_random n=100 m=100 k=50
tc testing-2 gen_random n=30 m=30 k=50
tc testing-3 gen_grids n=14 m=12 k=50 seed=123
tc testing-4 gen_grids n=70 m=12 k=50 extra=4
tc testing-5 gen_grids n=100 m=100 k=50 extra=10
tc testing-6 gen_grids n=100 m=14 k=50 twos=1
tc testing-7 gen_grids n=100 m=100 k=50 mode=ruin

group group5 15
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

group group6 20
limits n=1e15 m=1e15 k=50 strict=0
include_group group3
include_group group5
tc twoblock-imp1
tc large-1 gen_random k=50 n=123123123123123 m=123123123123124
tc large-2 gen_grids k=49 n=123123123123123 m=123123123123124 extra=10
tc large-3 gen_grids k=50 n=123123123123123 m=123123123123124 mode=ruin extra=10
tc large-4 gen_grids k=49 n=10 m=123123123123124 mode=ruin
tc large-5 gen_grids k=50 n=10 m=123123123123124
tc large-6 gen_grids k=50 n=123123123123124 m=10 mode=twopath mode=nopad

group group7 30
limits n=1e15 m=1e15 k=100000 strict=0
tc empty-1
tc empty-tall1
tc twoblock-imp1
tc large-1
tc large-2
tc large-3
tc large-4
tc large-5
tc large-6
tc testing-3
tc huge-1 gen_random k=100000 n=123123123123123 m=123123123123124
tc huge-2 gen_grids k=99000 n=123123123123124 m=123123123123124 extra=29000
tc huge-3 gen_grids k=99000 n=123123123123123 m=123123123123123 mode=ruin extra=29000 seed=125
tc huge-4 gen_grids k=100000 n=30000 m=123123123123124 mode=ruin
tc huge-5 gen_grids k=100000 n=30001 m=123123123123125 extra=5000
tc huge-6 gen_grids k=100000 n=18001 m=123123123123124 extra=1000
tc huge-7 gen_grids k=100000 n=15401 m=123123123123123 twos=1 extra=1000 seed=12
tc huge-8 gen_grids k=100000 n=18002 m=123123123123123 twos=2 extra=1000 seed=8
tc huge-9 gen_grids k=100000 n=18002 m=123123123123126 twos=1 extra=1000 mode=nopad seed=16
tc huge-10 gen_grids k=100000 n=18003 m=123123123123126 twos=1 extra=1000
tc huge-11 gen_grids k=100000 n=123123123123124 m=18000 mode=twopath seed=27
tc huge-12 gen_grids k=100000 n=123123123123124 m=28000 mode=twopath each=500 seed=1
tc huge-13 gen_grids k=100000 n=123123123123124 m=28000 mode=twopath each=500 seed=2

cleanup_programs
