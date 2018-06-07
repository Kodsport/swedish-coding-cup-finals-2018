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
n = int(float(cmdlinearg('n')))
k = int(float(cmdlinearg('k')))
same = int(eval(cmdlinearg('s')))
blim = int(float(cmdlinearg('b')))
clim = int(float(cmdlinearg('c', 1e9)))
dlim = int(float(cmdlinearg('d')))
assert 0 <= same < k

# add some with d = 0

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
