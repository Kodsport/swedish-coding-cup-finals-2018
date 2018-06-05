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
r = int(cmdlinearg('r'))
c = int(cmdlinearg('c'))
dst = int(cmdlinearg('dens'))

print(r, c)
G = [['*'] * c for _ in range(r)]

cnt = (r * c) // 9 * dst // 100

def is_free(x, y):
    for dx in range(3):
        for dy in range(3):
            if G[x + dx][y + dy] != '*': return False
    return True

def mark_used(x, y):
    for dx in range(3):
        for dy in range(3):
            G[x + dx][y + dy] = '.'

for _ in range(cnt):
    for _ in range(15):
        x = random.randint(0, r - 3)
        y = random.randint(0, c - 3)

        if is_free(x, y):
            mark_used(x, y)
            break

print('\n'.join(''.join(x) for x in G))
