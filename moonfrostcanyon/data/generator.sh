#!/usr/bin/env bash
PPATH=$(realpath ..)
. ../../testdata_tools/gen.sh

use_solution js_1.cpp

compile gen_norock.py
compile gen_r6.py
compile gen_random.py
compile gen_special.py

samplegroup
limits r=1000 c=1000 mode=general
sample 1
sample 2

group group1 10
limits r=999 c=999 mode=tilled
tc empty-1 gen_norock r=999 c=3
tc empty-2 gen_norock r=3 c=996
tc empty-3 gen_norock r=996 c=6
tc empty-4 gen_norock r=6 c=999
tc empty-5 gen_norock r=999 c=999

group group2 10
limits r=6 c=1000 mode=r6
tc 2
tc empty-4
tc r6-1 gen_r6 c=3
tc r6-2 gen_r6 c=6
tc r6-3 gen_r6 c=1000
tc r6-4 gen_r6 c=1000
tc r6-5 gen_r6 c=1000

group group3 20
limits r=1000 c=1000 mode=general
tc 1
tc 2
include_group group1
include_group group2
tc aspecial-1 gen_special case=0
tc random-1 gen_random r=1000 c=1000 dens=10
tc random-2 gen_random r=1000 c=1000 dens=10
tc random-3 gen_random r=1000 c=1000 dens=80
tc random-4 gen_random r=1000 c=1000 dens=80
tc random-5 gen_random r=1000 c=1000 dens=90
tc random-6 gen_random r=1000 c=1000 dens=90
tc random-7 gen_random r=1000 c=1000 dens=90
tc random-8 gen_random r=1000 c=1000 dens=130
tc random-9 gen_random r=1000 c=1000 dens=130
