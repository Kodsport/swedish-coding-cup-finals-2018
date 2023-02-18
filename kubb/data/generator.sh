#!/usr/bin/env bash
PPATH=$(realpath ..)
. ../../testdata_tools/gen.sh

use_solution ../precise.cpp opt

compile gen_random.py

samplegroup
limits mode=standard n=100
sample 1
sample 2
sample 3
sample 4
sample 5

group group1 5
limits mode=trivial n=5
tc 1
tc atrivial-1 gen_random mode=random n=5 zeroes=ac
tc atrivial-2 gen_random mode=random n=5 zeroes=ac

group group2 10
limits mode=standard n=10
tc 1
tc 2
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

group group3 15
limits mode=standard n=26
tc 1
tc 2
tc 3
tc 4
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

group group4 20
tc 2
limits mode=bad n=100
tc bsmall-special1
tc xbad-2 gen_random mode=static n=99 values=0.6,0,0.4
tc xbad-3 gen_random mode=static n=100 values=0.4,0,0.6
tc xbad-4 gen_random mode=static n=100 values=0.8,0,0.1
tc xbad-5 gen_random mode=random n=90 zeroes=ab

group group5 25
tc 1
tc 5
limits mode=even n=100
tc even-small1 gen_random mode=evil n=4 even=1
tc even-small2 gen_random mode=random n=2 even=1
tc even-small3 gen_random mode=random n=13 even=1
tc even-small4 gen_random mode=random n=14 even=1
tc even-small5 gen_random mode=evil n=15 even=1
tc even-small6 gen_random mode=evil n=16 even=1
tc even-evil1 gen_random mode=evil n=28 even=1
tc even-evil2 gen_random mode=evil n=28 even=1
tc even-evil3 gen_random mode=evil n=31 even=1
tc even-evil4 gen_random mode=evil n=34 even=1
tc even-evil5 gen_random mode=evil n=98 even=1
tc even-evil6 gen_random mode=evil n=99 even=1
tc even-evil7 gen_random mode=evil n=100 even=1
tc even-rand1 gen_random mode=random n=28 even=1
tc even-rand2 gen_random mode=random n=31 even=1
tc even-rand3 gen_random mode=random n=32 even=1
tc even-rand4 gen_random mode=random n=50 even=1
tc even-rand5 gen_random mode=random n=70 even=1
tc even-rand6 gen_random mode=random n=100 even=1
tc even-rand7 gen_random mode=random n=99 even=1
tc even-rand8 gen_random mode=random n=55 even=1
tc even-rand9 gen_random mode=random n=64 even=1
