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
zeroes = int(cmdlinearg('zeroes', 0))
ones = int(cmdlinearg('ones', 0))
larges = int(cmdlinearg('larges', 0))
n = int(cmdlinearg('n'))
k = int(cmdlinearg('k'))
smalls = int(cmdlinearg('smalls', 0))

prob = (k/n * 0.5) ** (1/k)
dev = 2 ** (1/k)
prob = random.uniform(prob/dev, prob*dev)
prob = min(prob, 1 - 1e-7)

a = [random.uniform(prob/dev, min(prob*dev, 1)) for _ in range(n)]

for _ in range(larges):
    a[random.randrange(n)] = random.uniform(prob, 1)

for _ in range(smalls):
    a[random.randrange(n)] = random.uniform(0, prob)

for _ in range(ones):
    a[random.randrange(n)] = 1

for _ in range(zeroes):
    a[random.randrange(n)] = 0

# 15 decimals is a lot
# a = ['{:.10}'.format(x) for x in a]
print(n, k)
print(*a)
