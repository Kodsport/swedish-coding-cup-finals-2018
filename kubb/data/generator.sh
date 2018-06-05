#!/usr/bin/env bash
PPATH=$(realpath ..)
. ../../testdata_tools/gen.sh

setup_dirs
use_solution ../precise.cpp opt

compile gen_random.py

samplegroup
limits mode=standard n=100
# sample 1
# sample 2
# sample 3
# sample 4

group group1 10
limits mode=trivial n=5
tc atrivial-1 gen_random mode=random n=5 zeroes=ac
tc atrivial-2 gen_random mode=random n=5 zeroes=ac

group group2 10
limits mode=standard n=10
include_group group1
tc small-evil1 gen_random mode=evil n=9
tc small-evil2 gen_random mode=evil n=10
tc bsmall-evil3 gen_random mode=evil n=10
tc small-rand1 gen_random mode=random n=9
tc small-rand2 gen_random mode=random n=9
tc small-rand3 gen_random mode=random n=10
tc small-rand4 gen_random mode=random n=10
tc small-rand5 gen_random mode=random n=10
tc bsmall-special1 gen_random mode=random n=1 zeroes=ab
tc bsmall-special2 gen_random mode=random n=1 zeroes=b
tc bsmall-special3 gen_random mode=random n=2 zeroes=c
tc bsmall-special4 gen_random mode=random n=2 zeroes=bc

group group3 10
limits mode=standard n=26
include_group group2
tc medium-evil1 gen_random mode=evil n=26
tc medium-evil2 gen_random mode=evil n=26
tc medium-evil3 gen_random mode=evil n=25
tc medium-evil4 gen_random mode=evil n=25
tc medium-rand1 gen_random mode=random n=22
tc medium-rand2 gen_random mode=random n=23
tc medium-rand3 gen_random mode=random n=24
tc medium-rand4 gen_random mode=random n=25
tc medium-rand5 gen_random mode=random n=26

group group4 10
limits mode=bad n=100
tc bsmall-special1
tc xbad-2 gen_random mode=static n=99 values=0.6,0,0.4
tc xbad-3 gen_random mode=static n=100 values=0.4,0,0.6
tc xbad-4 gen_random mode=static n=100 values=0.8,0,0.1
tc xbad-5 gen_random mode=random n=90 zeroes=ab

group group5 10
limits mode=standard n=100
include_group group3
include_group group4
tc large-evil1 gen_random mode=evil n=28
tc large-evil2 gen_random mode=evil n=31
tc large-evil3 gen_random mode=evil n=34
tc large-evil4 gen_random mode=evil n=98
tc large-evil5 gen_random mode=evil n=99
tc large-evil6 gen_random mode=evil n=100
tc large-rand1 gen_random mode=random n=28
tc large-rand2 gen_random mode=random n=31
tc large-rand3 gen_random mode=random n=32
tc large-rand4 gen_random mode=random n=50
tc large-rand5 gen_random mode=random n=70
tc large-rand6 gen_random mode=random n=100
tc large-rand7 gen_random mode=random n=99
tc large-rand8 gen_random mode=random n=55
tc large-rand9 gen_random mode=random n=64

cleanup_programs
