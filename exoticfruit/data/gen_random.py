#!/usr/bin/python3

import sys
import random


def cmdlinearg(name, default=None):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    assert default is not None, name
    return default

random.seed(int(cmdlinearg('seed', sys.argv[-1])))
n = int(cmdlinearg('n'))
k = int(cmdlinearg('k'))
same = int(cmdlinearg('s'))
blim = int(cmdlinearg('b'))
dlim = int(cmdlinearg('d'))

fruits = []

for _ in range(k-same):
	b = random.randint(0, blim)
	c = random.randint(0, 1e9)
	d = random.randint(0, dlim)
	fruits.append((b,c,d))

for _ in range(k-same, k):
	fruits.append(fruits[random.randrange(0,k-same)])

print(n, k)
for i in range(0,k):
	print(fruits[i][0], fruits[i][1], fruits[i][2])