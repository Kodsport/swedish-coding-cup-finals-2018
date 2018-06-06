#!/usr/bin/env bash
PPATH=$(realpath ..)
. ../../testdata_tools/gen.sh

setup_dirs
use_solution sol_ld_sl.cpp

compile gen_random.py

samplegroup
limits n=20 k=10
sample 1

group group1 15
limits n=1000 k=1000
tc small-allzero gen_random n=1000 k=10 zeroes=1000
tc small-tiny gen_random n=1 k=1
tc small-1 gen_random n=1000 k=1 larges=5 smalls=10
tc small-2 gen_random n=1000 k=1 zeroes=10
tc small-3 gen_random n=1000 k=10 ones=10 zeroes=10 larges=100 smalls=100
tc small-4 gen_random n=1000 k=100 zeroes=10 larges=100 smalls=3
tc small-5 gen_random n=1000 k=1000 ones=10

group group2 20
limits n=4e5 k=4e5
include_group group1
tc large-allzero gen_random n=400000 k=10 zeroes=400000
tc large-1 gen_random n=400000 k=1 larges=5 smalls=10
tc large-2 gen_random n=400000 k=1 zeroes=10
tc large-3 gen_random n=400000 k=10 ones=10 zeroes=10 larges=40000 smalls=40000
tc large-4 gen_random n=400000 k=80000 zeroes=5 larges=100000 smalls=7
tc large-5 gen_random n=400000 k=400000 ones=10

cleanup_programs
