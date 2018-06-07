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
clim = int(cmdlinearg('c', 1e9))
dlim = int(cmdlinearg('d'))

if same < 0:
    same = k + same

fruits = []

for _ in range(k-same):
    b = random.randint(0, blim)
    c = random.randint(0, clim)
    d = random.randint(0, dlim)
    fruits.append((b,c,d))

for i in range(k-same, k):
    fruits.append(fruits[random.randrange(i)])

print(n, k)
for i in range(k):
    print(*fruits[i])
