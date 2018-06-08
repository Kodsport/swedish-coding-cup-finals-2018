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
nozero = cmdlinearg('nozero', '')
b_lo = 1 if 'b' in nozero else 0
c_lo = 1 if 'c' in nozero else 0
d_lo = 1 if 'd' in nozero else 0
assert 0 <= same < k

# add some with zeroes

fruits = []

for _ in range(k-same):
    b = random.randint(b_lo, blim)
    c = random.randint(c_lo, clim)
    d = random.randint(d_lo, dlim)
    fruits.append((b,c,d))

for i in range(k-same, k):
    fruits.append(fruits[random.randrange(i)])

print(n, k)
for i in range(k):
    print(*fruits[i])
