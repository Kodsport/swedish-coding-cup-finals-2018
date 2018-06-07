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
tc d01 gen_random k=1e4 n=1e15 s=0 b=0 d=0
tc d02 gen_random k=1e4 n=1e15 s=0 b=1e9 d=0
tc d03 gen_random k=1e4 n=1e15 s=3000 b=1e9 d=0
tc d04 gen_random k=1e4 n=1 s=k-1 b=1e9 d=0
tc d05 gen_random k=1e4 n=1e15 s=k-1 b=1e9 d=0
tc d06 gen_random k=1e4 n=1e15 s=k-1 b=0 d=0
tc d07 gen_random k=1e4 n=1e15 s=k-2 b=10 d=0

group group2 15
limits n=1e15 k=1 b=1e9 d=1e9
tc k11 gen_random k=1 n=1e15 s=0 b=1e9 d=1e9
tc k12 gen_random k=1 n=1e15 s=0 b=1e5 d=1e9
tc k13 gen_random k=1 n=1e15 s=0 b=1e5 d=1e9
tc k14 gen_random k=1 n=1e15 s=0 b=1e9 d=1e9
tc k15 gen_random k=1 n=1e15 s=0 b=1e9 d=1e9

group group3 15
limits n=1e6 k=1e4 b=1e9 d=1e9
tc n51 gen_random k=1e4 n=1e6 s=0 b=1e9 d=1e9
tc n53 gen_random k=1e4 n=1e6 s=100 b=1e9 d=1e9
tc n54 gen_random k=1e4 n=1e6 s=1000 b=1e9 d=1e9
tc n55 gen_random k=1e4 n=1e6 s=k-1 b=1e9 d=1e9

group group4 25
limits n=1e15 k=1e4 b=1e9 d=1e9
include_group group1
include_group group2
include_group group3
tc large1 gen_random k=1e4 n=1e15 s=0 b=0 d=1e9
tc large2 gen_random k=1e4 n=1e15 s=k-2 b=0 d=1e9
tc large3 gen_random k=1e4 n=1e12 s=k*2//3 b=2 d=1e8
tc large4 gen_random k=1e4 n=1e12 s=k*2//3 b=10 d=1e8
tc large5 gen_random k=1e4 n=1e12 s=k*2//3 b=50 d=1e8
tc large6 gen_random k=1e4 n=1e10 s=k*2//3 b=100 d=1e6
tc large7 gen_random k=1e4 n=1e10 s=k-2 b=100 d=1e6
tc large8 gen_random k=1e4 n=1e15 s=1000 b=10 d=1e4
tc large9 gen_random k=1e4 n=1e15 s=1000 b=10 d=1e9

cleanup_programs
