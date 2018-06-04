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
zeroes = cmdlinearg('zeroes', '')
mode = cmdlinearg('mode')

if mode == 'random':
    a = random.uniform(0, 1)
    b = random.uniform(0, 1)
    c = random.uniform(0, 1)
elif mode == 'static':
    a,b,c = map(float, cmdlinearg('values').split(','))
else:
    assert mode == 'evil'
    AC = 0.3075
    B = 0.385
    eps = random.uniform(0, 0.1)
    a = AC + random.uniform(AC - eps, AC + eps)
    b = B + random.uniform(B - eps, B + eps)
    c = AC + random.uniform(AC - eps, AC + eps)

for x in zeroes:
    if x == 'a': a = 0
    if x == 'b': b = 0
    if x == 'c': c = 0

su = a + b + c
assert su > 0
su /= random.uniform(0.1, 0.9)
a /= su
b /= su
c /= su

print(n)
print(a, b, c)
