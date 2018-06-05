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
C = int(cmdlinearg('c'))

R = [['*'] * C for _ in range(6)]

cc = 0
while cc + 3 < C:
    p = random.uniform(0, 1)
    if p < 0.1:
        cc += 1
        continue
    elif p < 0.9:
        for k in range(3):
            for r in range(6):
                R[r][cc + k] = '.'
        cc += 3
    else:
        for k in range(3):
            for r in range(3):
                R[r + int((p - 0.9 - 1e-4) / 0.1 * 4)][cc + k] = '.'
        cc += 3

print(6, C)
print('\n'.join(''.join(x) for x in R))
