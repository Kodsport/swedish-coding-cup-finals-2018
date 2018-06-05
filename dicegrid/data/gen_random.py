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
m = int(cmdlinearg('m'))
k = int(cmdlinearg('k'))
blocked = []
blockeds = set()
for _ in range(k):
    while True:
        r = random.randrange(n)
        c = random.randrange(m)
        if (r, c) not in blockeds:
            blocked.append((r, c))
            blockeds.add((r, c))
            break

print(n, m, k)
for (r, c) in blocked:
    print(r+1, c+1)
