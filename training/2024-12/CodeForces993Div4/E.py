from math import *


def solve():
    k, l1, r1, l2, r2 = map(int, input().split())
    ans = 0
    cur = 1
    while cur <= r2:
        p = ceil(l2 / cur)
        q = floor(r2 / cur)
        if min(q, r1) - max(p, l1) + 1 > 0:
            ans += min(q, r1) - max(p, l1) + 1
        cur *= k
    print(ans)


t = int(input())
for i in range(t):
    solve()

"""
5
2 2 6 2 12
2 1 1000000000 1 1000000000
3 5 7 15 63
1000000000 1 5 6 1000000000
15 17 78 2596 20914861

12
1999999987
6
1
197
"""
