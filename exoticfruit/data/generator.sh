#!/usr/bin/env bash
PPATH=$(realpath ..)
. ../../testdata_tools/gen.sh

setup_dirs
use_solution bs_nested_sl.cpp opt

compile gen_random.py

samplegroup
limits n=1e15 k=100 b=1e9 d=1e9

group group1 10
limits n=1e15 k=1e4 b=1e9 d=0
tc d01 gen_random k=10000 n=1000000000000000 s=0 b=0 d=0
tc d02 gen_random k=10000 n=1000000000000000 s=0 b=1000000000 d=0
tc d03 gen_random k=10000 n=1000000000000000 s=3000 b=1000000000 d=0
tc d04 gen_random k=10000 n=1 s=-1 b=1000000000 d=0
tc d05 gen_random k=9999 n=1000000000000000 s=-1 b=1000000000 d=0
tc d06 gen_random k=9999 n=1000000000000000 s=-1 b=0 d=0
tc d07 gen_random k=9998 n=999999999999999 s=-2 b=10 d=0

group group2 15
limits n=1e15 k=1 b=1e9 d=1e9
tc k11 gen_random k=1 n=1000000000000000 s=0 b=1000000000 d=1000000000
tc k12 gen_random k=1 n=999999999999999 s=0 b=100000 d=1000000000
tc k13 gen_random k=1 n=1000000000000000 s=0 b=99999 d=1000000000
tc k14 gen_random k=1 n=1000000000000000 s=0 b=1000000000 d=999999999
tc k15 gen_random k=1 n=1000000000000000 s=0 b=999999999 d=999999999

group group3 15
limits n=1e6 k=1e4 b=1e9 d=1e9
tc n51 gen_random k=10000 n=1000000 s=0 b=1000000000 d=1000000000
tc n53 gen_random k=10000 n=1000000 s=100 b=1000000000 d=1000000000
tc n54 gen_random k=10000 n=1000000 s=1000 b=1000000000 d=1000000000
tc n55 gen_random k=10000 n=1000000 s=-1 b=1000000000 d=1000000000

group group4 25
limits n=1e15 k=1e4 b=1e9 d=1e9
include_group group1
include_group group2
include_group group3
tc large1 gen_random k=10000 n=1000000000000000 s=0 b=1000000000 d=1000000000
tc large2 gen_random k=10000 n=1000000000000000 s=100 b=1000000000 d=1000000000
tc large3 gen_random k=10000 n=1000000000000000 s=1000 b=1000000000 d=1000000000
tc large4 gen_random k=10000 n=1000000000000000 s=-1 b=1000000000 d=1000000000


cleanup_programs
