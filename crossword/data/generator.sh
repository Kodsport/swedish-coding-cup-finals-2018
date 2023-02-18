#!/usr/bin/env bash
PPATH=$(realpath ..)
. ../../testdata_tools/gen.sh

REQUIRE_SAMPLE_REUSE=0

use_solution ../partially_accepted/empty.cpp

compile gen_random.py pypy

samplegroup
limits t=0 n=8 m=10
sample_manual 1

gr() {
	g=$1
	n=$2
	m=$3
	d=$4
	f=$5
	group group$g 20
	limits t=$g n=$n m=$m
	tc c$g gen_random t=$g n=$n m=$m f=$f d=$d seed=$g
}

gr 1 50 50 0 0
gr 2 100 100 -1 0
gr 3 100 100 10 1
gr 4 100 100 35 0
gr 5 8 1000 30 1
