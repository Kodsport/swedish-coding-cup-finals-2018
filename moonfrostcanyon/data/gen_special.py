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
case = int(cmdlinearg('case'))

grids = [
# needs 4 colors
'''.....---XXX---...
.....---XXX---...
.....---XXX---...
.---XXX------XXX.
.---XXX------XXX.
.---XXX------XXX.
XXX---.....---XXX
XXX---.---.---XXX
XXX---.---.---XXX
.---XXX---XXX---.
.---XXX---XXX---.
.---XXX---XXX---.
.......---.......'''
]

grid = grids[case].replace('.', '*').replace('-', '.').replace('X', '.')
r = len(grid.split('\n'))
c = len(grid.split('\n')[0])
print(r, c)
print(grid)
