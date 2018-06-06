n, m, k = map(int, input().split())
grid = [['.'] * m for _ in range(n)]
for i in range(k):
    r,c = map(int, input().split())
    grid[r-1][c-1] = '#'
for x in grid:
    print(''.join(x))
