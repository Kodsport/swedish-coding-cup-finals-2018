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
maxk = int(cmdlinearg('k'))
mode = cmdlinearg('mode', '')
extra = int(cmdlinearg('extra', 0))
maxk -= extra
if 'ruin' in mode:
    maxk -= 1

blocked = []

def cover(u, l, d, r):
    global blocked
    hor = r - l
    vert = d - u
    ma = max(hor, vert)
    mi = min(hor, vert)
    special = random.sample(range(ma - 1), mi - 1)
    marked = [0] * ma
    for x in special:
        marked[x] = 1
    y = d - 1
    x = l
    for i in range(ma):
        blocked.append((y, x))
        if vert > hor:
            x += marked[i]
            y -= 1
        else:
            x += 1
            y -= marked[i]
    if len(blocked) >= maxk:
        del blocked[maxk-1:]

top = 0
left = 0
bottom = n
right = m
each = int(cmdlinearg('each', min(n, m, maxk) // 10 + 2))
forbid = 0
forbid2 = 0

lines = []
all_lines = []

if 'twopath' in mode:
    h = random.randint(1, right-left-2)
    cover(top+1, left+1, top+h+1, right-1)
    top += h+1
    right -= 1
    forbid2 = 1 << 3
    all_lines.append((0, 0, 1, right))
    all_lines.append((1, right-1, bottom, right))

twosat = random.sample(range(1, 10), int(cmdlinearg('twos', 0)))

count = 0
while bottom - top > 1 and right - left > 1:
    side = random.randrange(4)
    if (forbid | forbid2) & (1 << side):
        continue

    count += 1
    pad = 1
    line = None

    if count in twosat:
        if bottom - top == 2 or right - left == 2:
            break
        pad = 2
        forbid |= 1 << side
    h = random.randint(pad, min(each, right - left - 1, bottom - top - 1))
    h2 = int(h * 1.4)
    if side == 0:
        cover(top, left+pad, top + h, random.randrange(left+pad+1, min(left+pad+1 + h2, m)))
        line = (top, left, top + h, left + 1)
        top += h
        forbid &= ~(1 << 1)
    elif side == 1:
        cover(top+pad, left, random.randrange(top+pad+1, min(top+pad+1 + h2, n)), left + h)
        line = (top, left, top + 1, left + h)
        left += h
        forbid &= ~(1 << 0)
    elif side == 2:
        cover(bottom - h, random.randrange(max(0, right-pad-1 - h2), right-pad), bottom, right-pad)
        line = (bottom - h, right - 1, bottom, right)
        bottom -= h
        forbid &= ~(1 << 3)
    elif side == 3:
        cover(random.randrange(max(0, bottom-pad-1 - h2), bottom-pad), right - h, bottom-pad, right)
        line = (bottom - 1, right - h, bottom, right)
        right -= h
        forbid &= ~(1 << 2)
    else:
        assert False

    all_lines.append(line)

    if len(blocked) >= maxk-1:
        print("large gap", file=sys.stderr)
        break

    if line is not None and pad == 1:
        lines.append(line)

if bottom - top == 1 or right - left == 1:
    all_lines.append((top, left, bottom, right))

assert len(blocked) <= maxk
maxk += extra

if 'nopad' not in mode:
    blockeds = set(blocked)
    while len(blocked) < maxk:
        r = random.randrange(n)
        c = random.randrange(m)
        if r == c == 0:
            continue
        if r == n-1 or c == m-1:
            continue
        if (r, c) in blockeds:
            continue
        for line in all_lines:
            if line[0] <= r < line[2] and line[1] <= c < line[3]:
                break
        else:
            blocked.append((r, c))
            blockeds.add((r, c))

if 'ruin' in mode:
    line = random.choice(lines)
    y = random.randrange(line[0], line[2])
    x = random.randrange(line[1], line[3])
    blocked.append((y, x))

k = len(blocked)

random.shuffle(blocked)

if random.choice([True, False]):
    print(n, m, k)
    for (r, c) in blocked:
        print(r+1, c+1)
else:
    print(m, n, k)
    for (r, c) in blocked:
        print(c+1, r+1)
