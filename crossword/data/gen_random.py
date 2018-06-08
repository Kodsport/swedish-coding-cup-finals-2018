#!/usr/bin/pypy

from __future__ import print_function
import sys
import random

def cmdlinearg(name, default=None):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    assert default is not None, name
    return default

random.seed(int(cmdlinearg('seed', sys.argv[-1])))
t = int(cmdlinearg('t'))
n = int(cmdlinearg('n'))
m = int(cmdlinearg('m'))
dens = float(cmdlinearg('d'))
faraway = int(cmdlinearg('f')) 

wordlist = [x.strip() for x in open('../wordlist.txt')]
wordlistSet = set(wordlist)
uncommon = 'zqxjkvbpygfwmuclr'

def transpose(grid):
    n = len(grid)
    m = len(grid[0])
    grid2 = [['_'] * n for _ in range(m)]
    for i in range(n):
        for j in range(m):
            grid2[j][i] = grid[i][j]
    return grid2

def addword(grid, w):
    n = len(grid)
    m = len(grid[0])
    r = len(w)
    for i in range(n):
        for j in range(m):
            if j > 0 and grid[i][j-1] != '.':
                continue
            if j + r > m:
                continue
            if j + r != m and grid[i][j + r] != '.':
                continue
            works = True
            empty = True
            for k in range(r):
                if grid[i][j + k] != '.' and grid[i][j + k] != w[k]:
                    works = False
                    break
                if grid[i][j + k] != '.':
                    empty = False

            if works and not empty:
                for k in range(r):
                    before = ''
                    after = ''
                    for l in range(i-1, -1, -1):
                        if grid[l][j+k] != '.':
                            before = grid[l][j+k] + before
                        else:
                            break
                    for l in range(i+1, n):
                        if grid[l][j+k] != '.':
                            after = after + grid[l][j+k]
                        else:
                            break
                    st = before + w[k] + after
                    if len(st) > 1 and st not in wordlistSet:
                        works = False
                        break

                if works:
                    for k in range(r):
                        grid[i][j + k] = w[k]
                    return True
    return False


grid = [['.'] * m for _ in range(n)]
grid[random.randrange(n)][random.randrange(m)] = 'e'
for it in range(n*m*2):
    w = random.choice(wordlist)
    if random.choice([True, False]):
        grid = transpose(grid)
        addword(grid, w)
        grid = transpose(grid)
    else:
        addword(grid, w)

print(t)
print(n, m)
for i in range(n):
    line = grid[i]
    line2 = []
    for j in range(m):
        c = line[j]
        cond = (random.randrange(100) < dens) if dens != -1 else (random.uniform(0, 1) < 0.5 and i % 2)
        if cond and ((j == 0 or line2[j-1] == '.') and (i == 0 or grid[i-1][j] == '.') or dens == -1):
            if faraway:
                if i >= 2 and grid[i-2][j] != '.':
                    line2.append('.')
                elif j >= 2 and grid[i][j-2] != '.':
                    line2.append('.')
                elif i >= 1 and j >= 1 and grid[i-1][j-1] != '.':
                    line2.append('.')
                elif i >= 1 and j+1 < len(grid[i-1]) and grid[i-1][j+1] != '.':
                    line2.append('.')
                else:
                    line2.append(c)
            else:
                line2.append(c)
        else:
            line2.append('.')
    grid[i] = line2
    print(''.join(line2))
