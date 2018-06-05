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
n = 2
m = int(cmdlinearg('m'))
k = int(cmdlinearg('k'))
mode = cmdlinearg('mode')
assert mode in ['narrow', 'wide']

blocked = random.sample(range(m-2), k)
blocked.sort()

ind = random.randrange(1, k)

if mode == 'narrow':
    blocked[ind] = blocked[ind-1] + 2

for i in range(ind):
    blocked[i] = (1, blocked[i])
for i in range(ind, k):
    blocked[i] = (0, blocked[i])

random.shuffle(blocked)

print(n, m, k)
for (r, c) in blocked:
    print(r+1, c+1)
