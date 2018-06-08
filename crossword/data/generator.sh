#!/usr/bin/env bash
PPATH=$(realpath ..)
. ../../testdata_tools/gen.sh

setup_dirs
use_solution empty.cpp

compile gen_random.py pypy

samplegroup
limits t=0 n=8 m=10
# sample 1

gr() {
	g=$1
	n=$2
	m=$3
	d=$4
	f=$5
	group group$g 20
	limits t=$g n=$n m=$m
	tc $g gen_random t=$g n=$n m=$m f=$f d=$d seed=$g
}

gr 1 50 50 0 0
gr 2 100 100 10 1
gr 3 100 100 20 0
gr 4 100 100 -1 1
gr 5 8 500 20 1

cleanup_programs
