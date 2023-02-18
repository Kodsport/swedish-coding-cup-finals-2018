#!/usr/bin/env bash
PPATH=$(realpath ..)
. ../../testdata_tools/gen.sh

use_solution bs_nested_sl.cpp opt

compile gen_random.py

samplegroup
limits n=1e12 k=100 d=1e9
sample 1 # 5 2
sample 2 # 1e9 2
sample 3 # 1e7 2 d=0
sample 4 # 1e9 1 d=0
sample 5 # 1 1

group group1 10
limits n=1e12 k=1e4 d=0
tc d0-1 gen_random k=1e4 n=1e12 s=0 b=0 d=0         # pick all
tc d0-2 gen_random k=1e4 n=1e12 s=0 b=1e9 d=0       # pick half
tc d0-3 gen_random k=1e4 n=1e12 s=0 b=1e9 c=10 d=0  # pick nothing
tc d0-4 gen_random k=1e4 n=1e2 s=7000 b=1e9 d=0     # pick 100 best, and break bad binary searches with many same
tc d0-5 gen_random k=1e4 n=1 s=k-1 b=1e9 d=0        # n = 1 might also break binary searches
tc d0-6 gen_random k=1 n=1e12 s=0 b=1e9 d=0         # k = 1 might also break something
tc one-zero gen_random k=1 n=1e6 s=0 b=0 c=0 d=0    # doesn't matter, might trigger division by 0 or something
tc many-zero gen_random k=1e3 n=1e6 s=0 b=1 c=1 d=0 # some zeroes

group group2 10
limits n=1e12 k=1 d=1e9
tc 4 # 1e9 1 d=0
tc 5 # 1 1
tc one-1 gen_random k=1 n=1e12 s=0 b=1e9 d=1e9               # pick nothing
tc one-2 gen_random k=1 n=1e12 s=0 b=1 d=1e8 maxc=1 nozero=b # pick many (~1e9)
tc one-3 gen_random k=1 n=1e3 s=0 b=1 d=1e8 nozero=b         # pick all
tc aone-4 gen_random k=1 n=1e12 s=0 b=0 d=1e8                # pick all (b=0 and large n, finds precision errors)
tc one-zero

group group3 10
limits n=1e3 k=1e3 d=1e9 nozero=1
tc 1 # 5 2
tc 5 # 1 1
tc small-1 gen_random nozero=bcd k=1e3 n=1e3 s=0 b=1e9 d=1e9  # pick nothing
tc small-2 gen_random nozero=bcd k=1e3 n=1e3 s=0 b=10 d=1e7   # pick greedily
tc small-3 gen_random nozero=bcd k=1e3 n=1e3 s=0 b=1e9 d=2    # pick all the best
tc small-4 gen_random nozero=bcd k=1e3 n=1e3 s=k-2 b=1e7 d=10 # break bs
tc small-5 gen_random nozero=bcd k=1e3 n=1 s=k-2 b=1e9 d=10   # n = 1

group group4 10
limits n=1e6 k=1e4 d=1e9
tc 1 # 5 2
tc 5 # 1 1
tc medium-1 gen_random k=1e4 n=1e6 s=0 b=1e9 d=1e9         # pick nothing
tc medium-2 gen_random k=1e4 n=1e6 s=0 b=1e4 d=10          # pick greedily
tc medium-3 gen_random k=1e4 n=1e6 s=0 b=1e9 d=2           # pick all good
tc medium-4 gen_random k=1e4 n=1e6 s=k-2 b=1e5 d=10        # break bs
tc medium-5 gen_random k=1e4 n=1 s=5e3 b=1e9 d=10 nozero=d # n = 1
tc one-zero
tc many-zero

group group5 20
limits n=1e12 k=1e4 d=1e9
tc 1 # 5 2
tc 2 # 1e9 2
tc 3 # 1e7 2 d=0
tc 4 # 1e9 1 d=0
tc 5 # 1 1
include_group group1
include_group group4
tc one-2
tc one-3
tc aone-4
tc large-0 gen_random k=1e4 n=1e12 s=2 b=1e8 d=1e8     # pick nothing
tc large-1 gen_random k=1e4 n=1e12 s=0 b=0 d=1e7       # pick all
tc large-2 gen_random k=1e4 n=1e12 s=k-2 b=0 d=1e7     # pick all, with many duplicates
tc large-3 gen_random k=1e4 n=1e12 s=k*2//3 b=2 d=1e8
tc large-4 gen_random k=1e4 n=1e12 s=k*2//3 b=10 d=1e8
tc large-5 gen_random k=1e4 n=1e12 s=k*2//3 b=50 d=1e7 nozero=b
tc large-6 gen_random k=1e4 n=1e10 s=k*2//3 b=100 d=1e6
tc large-7 gen_random k=1e4 n=1e10 s=k-2 b=100 d=1e6
tc large-8 gen_random k=1e4 n=1e12 s=1000 b=10 d=1e2
tc large-9 gen_random k=1e4 n=1e12 s=1000 b=10 d=1e6
